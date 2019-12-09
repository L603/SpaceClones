#ifndef ASSETCOMMON_H
#define ASSETCOMMON_H

#include <filesystem>
#include <SFML/Graphics.hpp>
#include <fontconfig/fontconfig.h>

#include "config.h"
#include "types.h"

/// Una clase con los datos necesarios para crear los path's de los assets
class AssetCommon
{
private:
	FcConfig* config;

	fs::path preffix;
	fs::path fontPath;
	sf::Font myFont;

	void setPreffix();
	fs::path getFontPath(std::string fontName);
	void setFont();

	friend class GameObject;
public:
	AssetCommon();
	virtual ~AssetCommon();

	void recalculateAssets();

	sf::Font& getFont();
};

#endif /* ASSETCOMMON_H */
