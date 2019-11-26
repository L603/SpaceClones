#ifndef ASSETCOMMON_H
#define ASSETCOMMON_H

#include <filesystem>
#include <SFML/Graphics.hpp>

#include "config.h"
#include "types.h"

/// Una clase con los datos necesarios para crear los path's de los assets
class AssetCommon
{
private:
	fs::path preffix;
	fs::path fontPath;
	sf::Font myFont;

	void setPreffix();
	void setFontPath();
	void setFont();

	friend class GameObject;
public:
	AssetCommon();
	virtual ~AssetCommon();

	void recalculateAssets();
};

#endif /* ASSETCOMMON_H */
