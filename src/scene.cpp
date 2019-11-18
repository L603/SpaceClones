#include <SFML/Graphics.hpp>
#include "scene.h"
#include "nave.h"

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

void Scene::render()
{
	for(const auto i:renderObjects)
	{
		window.draw(*i.lock());
	}
}

void Scene::start()
{
	auto nave = Nave::spawn(*this);
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

		// Aquí es donde se renderiza todo
		render();

		window.display();
	}
}

/// Esta función añade los GameObject's a la lista interna de la escena.
std::weak_ptr<GameObject> Scene::addObject(GameObject* newObject)
{
	// El puntero libre es encapsulado
	auto newPointer = std::shared_ptr<GameObject>(newObject);
	objects.push_back(newPointer);

	// Añadiendo a la lista de objetos para renderizar
	auto newRenderable = std::dynamic_pointer_cast<sf::Drawable>(newPointer);
	if(newRenderable)
	{
		renderObjects.push_back(newRenderable);
	}

	return newPointer;
}
