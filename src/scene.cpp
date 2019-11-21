#include <thread>
#include <iostream>
#include <chrono>
#include <ctime>
#include <memory>
#include <SFML/Graphics.hpp>

#include "scene.h"
#include "nave.h"

Scene::Scene():
	window(
		sf::VideoMode::getFullscreenModes()[0],
		"Clones",
		// El fullscreen no funciona si la pantalla principal no está activada.(Xorg)
		sf::Style::Fullscreen
	),
	collisionMatrix(
		{
			{
				RigidBody::faction::alien,
				{
					{RigidBody::faction::alien,  0},
					{RigidBody::faction::nave,   1},
					{RigidBody::faction::escudo, 1}
				}
			},
			{
				RigidBody::faction::nave,
				{
					{RigidBody::faction::alien,  1},
					{RigidBody::faction::nave,   0},
					{RigidBody::faction::escudo, 1}
				}
			},
			{
				RigidBody::faction::escudo,
				{
					{RigidBody::faction::alien,  0},
					{RigidBody::faction::nave,   0},
					{RigidBody::faction::escudo, 0}
				}
			}
		}
	)
	{};

Scene::~Scene(){};

sf::RenderWindow& Scene::getWindow()
{
	return window;
}

void Scene::render()
{
	// Renderiza lo renderizable
	for(size_t i = 0; i < renderObjects.size(); i++)
	{
		window.draw(*renderObjects[i].lock());
	}
	window.display();
}
void Scene::physicsUpdate()
{
	// Esto es O(n^2)
	// Hay mucho que mejorar
	for(auto ii = collisionMatrix.begin(); ii != collisionMatrix.end(); ii++)
	{
		auto row = ii->second;
		RigidBody::faction factionA = ii->first;

		for(auto jj = row.begin(); jj != row.end(); jj++)
		{
			RigidBody::faction factionB = jj->first;
			if(jj->second && rigidBodies.size() > 0)
			{
				auto rigidA = rigidBodies.find(factionA);
				auto rigidB = rigidBodies.find(factionB);

				// Si alguno de los vectores de rigidbodies está vacío
				if(rigidA == rigidBodies.end() || rigidB == rigidBodies.end())
				{
					continue;
				}
				auto rigidVectorA = rigidA->second;
				auto rigidVectorB = rigidB->second;

				for(const auto kk: rigidVectorA)
				{
					for(const auto ll: rigidVectorB)
					{
						kk.lock()->checkCollision(ll);
					}
				}
			}
		}
	}
}

void Scene::update()
{
	// Actualiza todos los objetos
	for(size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->update();
	}
}

void Scene::postUpdate()
{
	// Esto elimina los objetos que están marcados para eliminar
	auto newEnd = std::remove_if(objects.begin(), objects.end(),
		[](std::shared_ptr<GameObject> i)
		{
			return i->isDeletable;
		});
	objects.erase(newEnd, objects.end());

	// Esto elimina los punteros expirados
	auto newRenderEnd = std::remove_if(renderObjects.begin(), renderObjects.end(),
		[](std::weak_ptr<sf::Drawable> i)
		{
			return i.expired();
		});
	renderObjects.erase(newRenderEnd, renderObjects.end());
}

void Scene::start()
{
	auto start = std::chrono::system_clock::now();
	std::chrono::system_clock::time_point lastTick;
	std::chrono::system_clock::time_point tick = start;

	auto posNave = sf::Vector2f(window.getSize().x*0.5f, window.getSize().y*0.8f);
	auto nave2 = Nave::spawn(*this, posNave);

	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			switch(event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				default:
					break;
			}
		}
		lastTick = tick;
		tick = std::chrono::system_clock::now();

		deltaTime = (tick - lastTick).count()*0.000000001f;
		std::cout << deltaTime << '\n';

		// Actualizaciones y esas cosas
		physicsUpdate();
		update();
		render();
		postUpdate();

		//std::this_thread::sleep_for(std::chrono::milliseconds(20));
		window.clear();
	}
}

std::weak_ptr<GameObject> Scene::addObject(GameObject* newObject)
{
	// El puntero libre es encapsulado
	auto newPointer = std::shared_ptr<GameObject>(newObject);
	objects.push_back(newPointer);

	// Añadiendo a la lista de objetos para renderizar
	auto newRenderable = std::dynamic_pointer_cast<sf::Drawable>(newPointer);
	if(newRenderable)
	{
		renderObjects.push_back(newRenderable);
	}

	// Añadiendo a la lista de listas de objetos colisionables
	auto newRigid = std::dynamic_pointer_cast<RigidBody>(newPointer);
	if(newRigid)
	{
		rigidBodies[newRigid->getFaction()].push_back(newRigid);
	}

	return newPointer;
}
