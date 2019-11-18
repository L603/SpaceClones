#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>
//#include <Box2D/Box2D.h>
#include <vector>
#include <memory>


class Scene;

class GameObject : public sf::Transformable
{
protected:
	Scene* myScene;

	GameObject(Scene& _myScene);
	std::weak_ptr<GameObject> addToList();
public:
	virtual void update()=0;
	virtual ~GameObject();
};

#endif /* GAMEOBJECT_H */
