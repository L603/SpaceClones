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

public:
	AssetCommon();
	virtual ~AssetCommon();
};

#endif /* ASSETCOMMON_H */
