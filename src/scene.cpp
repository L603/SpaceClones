#include <SFML/Graphics.hpp>
#include "scene.h"

Scene::Scene():
	gravity(0.f,0.f),
	world(gravity),
	window(
		sf::VideoMode::getFullscreenModes()[0],
		"Clones",
		// El fullscreen no funciona si la pantalla principal no está activada.(Xorg)
		sf::Style::Fullscreen
	){};

Scene::~Scene(){};

sf::RenderWindow& Scene::getWindow()
{
	return window;
}

void Scene::start()
{
	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			switch(event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				default:
					break;
			}
		}

		window.clear();

		sf::CircleShape cir(100);

		sf::Vector2f pos = (sf::Vector2f)window.getSize()*0.5f;
		pos -= sf::Vector2f(cir.getRadius(),cir.getRadius());

		cir.setPosition(pos);

		cir.setFillColor(sf::Color(255, 255, 255));

		window.draw(cir);

		window.display();
	}
}
std::weak_ptr<GameObject> Scene::addObject(GameObject* newObject)
{
	auto newPointer = std::shared_ptr<GameObject>(newObject);
	objects.push_back(newPointer);
	return newPointer;
}
