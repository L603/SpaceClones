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
		window.display();
	}

	return 0;
}
