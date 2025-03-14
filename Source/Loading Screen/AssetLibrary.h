#pragma once

#include "Dependencies.h"

class AssetLibrary
{
	static AssetLibrary* i;
	
	AssetLibrary();
	AssetLibrary(const AssetLibrary&) = delete;
	AssetLibrary& operator=(const AssetLibrary&) = delete;



public:
	static AssetLibrary* Get();
	void Destroy();

	
	void LoadFont();
	sf::Font Font;
};