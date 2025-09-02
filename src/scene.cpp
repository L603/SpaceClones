#include <thread>
#include <iostream>
#include <chrono>
#include <ctime>
#include <cmath>
#include <memory>
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "scene.h"
#include "alien.h"
#include "alienSpawner.h"
#include "nave.h"
#include "escudos.h"
#include "assetCommon.h"
#include "puntaje.h"

Scene::Scene():
	window(
		sf::VideoMode::getFullscreenModes()[0],
		"Clones",
		// El fullscreen no funciona si la pantalla principal no está activada.(Xorg)
		sf::Style::Default,
		sf::State::Fullscreen
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
	),
	pathGen()
	{};

Scene::~Scene(){};

sf::RenderWindow& Scene::getWindow()
{
	return window;
}

AssetCommon& Scene::getPathGen()
{
	return pathGen;
}
std::weak_ptr<Puntaje> Scene::getPoints()
{
	return thePoints;
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

void Scene::inputUpdate()
{
	xAxis = 0.f;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		xAxis += 1.f;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		xAxis += -1.f;
	}

	// Esto hace que el movimiento sea más suave.
	// Es una equación diferencial
	smoothxAxis = lerp(smoothxAxis, xAxis, 1- std::pow(1.f - smooth, deltaTime));
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
		}
	);
	objects.erase(newEnd, objects.end());

	// Esto elimina los punteros expirados
	auto newRenderEnd = std::remove_if(renderObjects.begin(), renderObjects.end(),
		[](std::weak_ptr<sf::Drawable> i)
		{
			return i.expired();
		}
	);
	renderObjects.erase(newRenderEnd, renderObjects.end());

	// Esto elimina los rigidBodies expirados
	for(auto ii = rigidBodies.begin(); ii != rigidBodies.end(); ii++)
	{
		auto newBodyEnd = std::remove_if(ii->second.begin(), ii->second.end(),
			[](std::weak_ptr<RigidBody> i)
			{
				return i.expired();
			}
		);
		ii->second.erase(newBodyEnd, ii->second.end());
	}
}

void Scene::start()
{
	// Cosas necesarias para el deltaTime
	auto start = std::chrono::system_clock::now();
	std::chrono::system_clock::time_point lastTick;
	std::chrono::system_clock::time_point tick = start;

	// GameObjects spawneados al inicio del juego
	auto posNave = sf::Vector2f(window.getSize().x*0.5f, window.getSize().y*0.9f);
	auto posPuntaje = sf::Vector2f(window.getSize().x*0.025f, window.getSize().y*0.025f);

	auto nave2 = Nave::spawn(*this, posNave);
	thePoints = Puntaje::spawn(*this, posPuntaje);

	// Aliens
	auto spawner = AlienSpawner::spawn(*this);
	spawner.lock()->spawnAliens();

	//Escudo Izquierdo
	auto gPos=0.7f;
	auto ggPos=0.0f;

	for(size_t a=0; a<50; a++)
	{
		auto posEscudos=sf::Vector2f(window.getSize().x*ggPos, window.getSize().y*gPos);
		auto escudos3=Escudos::spawn(*this,posEscudos);
		ggPos+=(0.5f-0.1f)/100.f;
	}

	//Escudo Central
	auto tPos=0.7f;
	auto ttPos=0.4f;

	for(size_t a=0; a<50; a++)
	{
		auto posEscudos=sf::Vector2f(window.getSize().x*ttPos, window.getSize().y*tPos);
		auto escudos4=Escudos::spawn(*this,posEscudos);
		ttPos+=(0.5f-0.1f)/100.f;
	}


	//Escudo Derecha
	auto uPos=0.7f;
	auto uuPos=0.8f;

	for(size_t a=0; a<50; a++){
		auto posEscudos=sf::Vector2f(window.getSize().x*uuPos, window.getSize().y*uPos);
		auto escudos4=Escudos::spawn(*this,posEscudos);
		uuPos+=(0.5f-0.1f)/100.f;
	}

	while(window.isOpen())
	{
		while(auto event = window.pollEvent())
		{
			// TODO: Visitor
			if(event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}
		lastTick = tick;
		tick = std::chrono::system_clock::now();

		deltaTime = (tick - lastTick).count()*0.000000001f;

		// Actualizaciones y esas cosas
		inputUpdate();
		physicsUpdate();
		update();
		render();
		postUpdate();

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


axisT Scene::getXAxis()
{
	return xAxis;
}

axisT Scene::getSmoothXAxis()
{
	return smoothxAxis;
}

axisT Scene::lerp(axisT a, axisT b, timeT t)
{
	return a + t*(b - a);
}
