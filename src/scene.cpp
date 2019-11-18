#include <thread>
#include <chrono>
#include <memory>
#include <SFML/Graphics.hpp>

#include "scene.h"
#include "nave.h"

Scene::Scene():
	//gravity(0.f,0.f),
	//world(gravity),
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
	//for(auto i = renderObjects.begin(); i != renderObjects.end(); i++)
	//{
		//window.draw(*i->lock());
	//}
	for(size_t i = 0; i < renderObjects.size(); i++)
	{
		window.draw(*renderObjects[i].lock());
	}
}

void Scene::update()
{
	//for(auto i = objects.begin(); i != objects.end(); i++)
	//{
		//(*i)->update();
	//}
	for(size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->update();
	}
}

void Scene::start()
{
	auto nave2 = Nave::spawn(*this, (sf::Vector2f)window.getSize()*0.5f);

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

		update();

		// Aquí es donde se renderiza todo
		render();

		window.display();
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
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
