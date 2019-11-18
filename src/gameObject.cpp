#include "gameObject.h"
#include "scene.h"

GameObject::GameObject(Scene& _myscene):
	myScene(&_myscene),
	isDeletable(false){};

GameObject::~GameObject(){};

void GameObject::despawn()
{
	isDeletable = true;
}

std::weak_ptr<GameObject> GameObject::addToList()
{
	return myScene->addObject(this);
}
