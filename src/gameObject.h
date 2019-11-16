#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <vector>

class Scene;

class GameObject
{
private:
	Scene* myScene;

public:
	GameObject(Scene* newScene);
	virtual ~GameObject();
};

#endif /* GAMEOBJECT_H */
