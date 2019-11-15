#include <iostream>
#include <thread>
#include <chrono>
#include <SFML/Graphics.hpp>

int main(int argc, char *argv[])
{
	std::cout << "Hello world\n";

	sf::RenderWindow window(sf::VideoMode(), "Clones", sf::Style::Fullscreen);

	return 0;
}
