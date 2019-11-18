#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>
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
	bool isDeletable;

	void despawn();

	virtual void update()=0;
	virtual ~GameObject();
};

#endif /* GAMEOBJECT_H */
