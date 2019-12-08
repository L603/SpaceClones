#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ext/stdio_filebuf.h>
#include <fstream>
#include <fontconfig/fontconfig.h>

#include "assetCommon.h"
#include "config.h"
#include "types.h"

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
	FcConfig* config = FcInitLoadConfigAndFonts();

	FcPattern* pattern = FcNameParse((const FcChar8*)"LiberationMono-Regular");

	FcConfigSubstitute(config, pattern, FcMatchPattern);
	FcDefaultSubstitute(pattern);

	FcResult result = FcResultNoMatch;
	FcPattern* font = FcFontMatch(config, pattern, &result);
	if(font)
	{
		FcChar8* file = NULL;
		if (FcPatternGetString(font, FC_FILE, 0, &file) == FcResultMatch)
		{
			fontPath = (char*)file;
		}
	}
	FcPatternDestroy(font);
	FcPatternDestroy(pattern);

	FcConfigDestroy(config);
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

sf::Font& AssetCommon::getFont()
{
	return myFont;
}
