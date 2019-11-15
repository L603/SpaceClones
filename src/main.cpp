#include <iostream>
#include <thread>
#include <chrono>
#include <SFML/Graphics.hpp>

int main(int argc, char *argv[])
{
	sf::RenderWindow window(sf::VideoMode(), "Clones", sf::Style::Fullscreen);

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

	return 0;
}
