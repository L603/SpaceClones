#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <memory>

#include "gameObject.h"
#include "rigidBody.h"

class Scene
{
private:

	//b2Vec2 gravity;
	//b2World world;
	sf::RenderWindow window;

	std::vector<std::shared_ptr<GameObject>> objects;
	std::vector<std::weak_ptr<sf::Drawable>> renderObjects;

	void update();
	void render();
	void postUpdate();

public:
	Scene();
	virtual ~Scene();

	sf::RenderWindow& getWindow();
	std::weak_ptr<GameObject> addObject(GameObject* newObject);

	void start();
};

#endif /* SCENE_H */
