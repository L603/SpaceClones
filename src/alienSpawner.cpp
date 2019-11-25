#include <SFML/Graphics.hpp>

#include "alienSpawner.h"
#include "scene.h"

AlienSpawner::AlienSpawner(Scene& _myScene):GameObject(_myScene){};

AlienSpawner::~AlienSpawner(){};

void AlienSpawner::spawnAliens()
{
	// Aliens
	auto xPos = 0.1f;
	for(size_t ii = 0; ii < 6 ; ii++)
	{
		auto yPos = 0.1f;
		for(size_t jj = 0; jj < 5 ; jj++)
		{
			auto posAlien = sf::Vector2f(myScene->getWindow().getSize().x*xPos, myScene->getWindow().getSize().y*yPos);
			Alien::spawn(*myScene, posAlien);
			yPos += (0.5f-0.1f)/4.f;
		}
		xPos += (0.9f-0.1f)/5.f;
	}
}

std::weak_ptr<AlienSpawner> AlienSpawner::spawn(Scene& _myScene)
{
	// Creo un nuevo alienSpawer
	AlienSpawner *newAlienSpawner = new AlienSpawner(_myScene);

	// Añado la nave a la lista de objetos de la escena
	auto smartPtr = newAlienSpawner->addToList();

	// Convierto el smart pointer de la clase base a AlienSpawner
	auto newPointer = std::dynamic_pointer_cast<AlienSpawner>(smartPtr.lock());

	return newPointer;
}
