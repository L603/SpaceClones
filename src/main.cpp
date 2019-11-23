#include <iostream>
#include <SFML/Graphics.hpp>
#include <filesystem>

#include "scene.h"
#include "types.h"

int main(int argc, char *argv[])
{
	// Verificando si el programa está instalado
	if(fs::current_path().parent_path().filename() != "bin")
	{
		std::cout << "OOF\n";
	}

	Scene escena;

	escena.start();

	return 0;
}
