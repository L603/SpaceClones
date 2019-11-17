#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <vector>


class Scene;

class GameObject : public sf::Transformable
{
private:
	Scene* myScene;

public:
	GameObject(Scene* _myScene);
	virtual ~GameObject();
};

#endif /* GAMEOBJECT_H */
