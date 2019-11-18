#include "gameObject.h"
#include "scene.h"

GameObject::GameObject(Scene& _myscene):
	myScene(&_myscene){};

GameObject::~GameObject(){};

std::weak_ptr<GameObject> GameObject::addToList()
{
	return myScene->addObject(this);
}
