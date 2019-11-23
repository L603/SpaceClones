#include <iostream>
#include <SFML/Graphics.hpp>
#include <filesystem>

#include "scene.h"
#include "types.h"

int main(int argc, char *argv[])
{
	// Verificando si el programa está instalado
	fs::path preffix = fs::current_path().filename();
	if(preffix != "bin")
	{
		std::cout << "OOF\n";
	}

	Scene escena;

	escena.start();

	return 0;
}
