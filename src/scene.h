#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <vector>

#include "gameObject.h"


class Scene
{
private:

	b2Vec2 gravity;
	b2World world;
	sf::RenderWindow window;

	std::vector<std::unique_ptr<GameObject>> objects;

public:
	Scene();
	virtual ~Scene();

	sf::RenderWindow& getWindow();

	void render();
};

#endif /* SCENE_H */
