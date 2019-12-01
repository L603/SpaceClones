#include <iostream>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <fontconfig/fontconfig.h>

#include "scene.h"
#include "types.h"

int main(int argc, char *argv[])
{

	if(!FcInit())
	{
		std::cerr << "Fontconfig no funciona\n";
		exit(3);
	}

	Scene escena;

	escena.start();

	return 0;
}
