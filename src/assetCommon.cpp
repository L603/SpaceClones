#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ext/stdio_filebuf.h>
#include <fstream>

#include "assetCommon.h"
#include "config.h"
#include "types.h"

#define fontPathCmd "fc-list | grep LiberationMono-Regular | sed \"s/\\(.*\\):.*:.*/\\1/g\""

AssetCommon::AssetCommon()
{
	// Obteniendo el preffix del path de los assets

	fs::path currentPath = fs::current_path();

	// Si el programa está corriendo donde se compiló
	if(currentPath == BUILD_BIN_DIR)
	{
		preffix = fs::path(BUILD_DATA_DIR);
	}
	else
	{
		preffix = fs::path(DATA_DIR);
	}

	// Obteniendo el path de la fuente:

	FILE *fontPathFILE = popen(fontPathCmd, "r");
	if(!fontPathFILE)
	{
		std::cerr << "Fuente no encontrada\n";
		exit(1);
	}

	// Esta clase es no estándar c++ . No funciona en windows
	__gnu_cxx::stdio_filebuf<char> _fontBuf(fontPathFILE, std::ios::in);
	std::istream fontBuf(&_fontBuf);

	fontBuf >> fontPath;

	pclose(fontPathFILE);
}

AssetCommon::~AssetCommon(){};
