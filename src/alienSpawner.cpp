#include <SFML/Graphics.hpp>

#include "alienSpawner.h"
#include "scene.h"
#include "gameObject.h"

AlienSpawner::AlienSpawner(Scene& _myScene):
	GameObject(_myScene),
	alienVel(100){};

AlienSpawner::~AlienSpawner(){};

void AlienSpawner::spawnAliens()
{
	// Aliens
	auto xPos = 0.1f;
	for(size_t ii = 0; ii < 6 ; ii++)
	{
		auto yPos = 0.1f;
		aliens.push_back(std::vector<std::weak_ptr<Alien>>());
		for(size_t jj = 0; jj < 5 ; jj++)
		{
			auto posAlien = sf::Vector2f(myScene->getWindow().getSize().x*xPos, myScene->getWindow().getSize().y*yPos);
			aliens.at(ii).push_back(Alien::spawn(*myScene, posAlien));
			yPos += (0.5f-0.1f)/4.f;
		}
		xPos += (0.9f-0.1f)/5.f;
	}

}

void AlienSpawner::update()
{
	for(auto ii = aliens.begin(); ii != aliens.end(); ii++)
	{
		for(auto jj = ii->begin(); jj != ii->end(); jj++)
		{
			if(!jj->expired())
			{
				sf::Vector2f deltaPos(alienVel*deltaTime(), 0.f);
				jj->lock()->GameObject::move(deltaPos);
			}
		}
	}

	if(timeTank > 1.f)
	{
		alienVel *= -1;

		for(auto ii = aliens.begin(); ii != aliens.end(); ii++)
		{
			for(auto jj = ii->begin(); jj != ii->end(); jj++)
			{
				if(!jj->expired())
				{
					sf::Vector2f deltaPos(0.f, 10.f);
					jj->lock()->GameObject::move(deltaPos);
				}
			}
		}

		timeTank = 0.f;
	}

	timeTank += deltaTime();
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
