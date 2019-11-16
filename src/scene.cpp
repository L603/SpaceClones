#include <SFML/Graphics.hpp>
#include "scene.h"

Scene::Scene():
	gravity(0.f,0.f),
	world(gravity),
	window(sf::VideoMode(), "Clones", sf::Style::Fullscreen){};

Scene::~Scene(){};

sf::RenderWindow& Scene::getWindow()
{
	return window;
}
