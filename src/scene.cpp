#include <thread>
#include <iostream>
#include <chrono>
#include <memory>
#include <SFML/Graphics.hpp>

#include "scene.h"
#include "nave.h"

Scene::Scene():
	//gravity(0.f,0.f),
	//world(gravity),
	window(
		sf::VideoMode::getFullscreenModes()[0],
		"Clones",
		// El fullscreen no funciona si la pantalla principal no está activada.(Xorg)
		sf::Style::Fullscreen
	){};

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
	// Creo que esta cosa verifica las colisiones.
	// Podría estar mejor.
	for(const auto ii: collisionMatrix)
	{
		const RigidBody::faction factionA = ii.first;
		for(const auto jj: ii.second)
		{
			const RigidBody::faction factionB = jj.first;
			if(jj.second)
			{
				for(const auto kk: rigidBodies.at(factionA))
				{
					for(const auto ll: rigidBodies.at(factionB))
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

		// Actualizaciones y esas cosas
		physicsUpdate();
		update();
		render();
		postUpdate();

		std::this_thread::sleep_for(std::chrono::milliseconds(20));
		window.clear();
	}
}

/// Esta función añade los GameObject's a la lista interna de la escena.
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
