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
	recalculateAssets();
}

AssetCommon::~AssetCommon(){};

void AssetCommon::setPreffix()
{
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
}

void AssetCommon::setFontPath()
{
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

void AssetCommon::setFont()
{
	setFontPath();
	if(!myFont.loadFromFile(fontPath))
	{
		std::cerr << "No se pudo cargar la fuente\n";
		exit(2);
	}
}

void AssetCommon::recalculateAssets()
{
	setPreffix();
	setFont();
}
