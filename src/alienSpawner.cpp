#include <SFML/Graphics.hpp>

#include "alienSpawner.h"

AlienSpawner::AlienSpawner(Scene& _myScene):GameObject(_myScene){};

AlienSpawner::~AlienSpawner(){};

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
