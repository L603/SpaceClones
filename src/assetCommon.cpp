#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <fontconfig/fontconfig.h>

#include "assetCommon.h"
#include "config.h"
#include "types.h"

AssetCommon::AssetCommon():
	config(FcInitLoadConfigAndFonts())
{
	recalculateAssets();
}

AssetCommon::~AssetCommon()
{
	FcConfigDestroy(config);
}

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

fs::path AssetCommon::getFontPath(std::string fontName)
{
	fs::path resu;

	// EL patrón de la fuente para FontConfig
	FcPattern* pattern = FcNameParse((const FcChar8*)fontName.c_str());

	// Por alguna razón hay que llamar estas funciones antes
	// del FcFontMatch()
	FcConfigSubstitute(config, pattern, FcMatchPattern);
	FcDefaultSubstitute(pattern);

	// Buscando la fuente más cercana
	FcResult result = FcResultNoMatch;
	FcPattern* font = FcFontMatch(config, pattern, &result);
	if(font)
	{
		// Al parecer el FcPatternDestroy(font) libera esto.
		// Solo es una referencia a un miembro de font.
		FcChar8* file = NULL;

		switch (FcPatternGetString(font, FC_FILE, 0, &file))
		{
			case FcResultNoMatch:
			case FcResultTypeMismatch:
			case FcResultNoId:
			case FcResultOutOfMemory:
				std::cerr <<  "No existe ninguna fuente adecuada instalada\n";
				exit(3);

			case FcResultMatch:
				resu = (char*)file;
				break;
		}
	}

	// Liberando memoria
	FcPatternDestroy(font);
	FcPatternDestroy(pattern);

	return resu;
}

void AssetCommon::setFont()
{
	fontPath = getFontPath("LiberationMono");
	if(!myFont.openFromFile(fontPath))
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
