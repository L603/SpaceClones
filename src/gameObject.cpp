#include "gameObject.h"
#include "scene.h"
#include "types.h"

GameObject::GameObject(Scene& _myscene):
	myScene(&_myscene),
	isDeletable(false){};

GameObject::~GameObject(){};

timeT GameObject::deltaTime()
{
	return myScene->deltaTime;
}

void GameObject::despawn()
{
	// Desawpnea al objeto
	isDeletable = true;
}

std::weak_ptr<GameObject> GameObject::addToList()
{
	// Añade el nuevo objeto a la lista de la escena
	return myScene->addObject(this);
}
