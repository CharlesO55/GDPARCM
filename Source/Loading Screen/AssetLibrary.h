#pragma once

#include "Dependencies.h"

class AssetLibrary
{
	static AssetLibrary* i;
	
	AssetLibrary();
	AssetLibrary(const AssetLibrary&) = delete;
	AssetLibrary& operator=(const AssetLibrary&) = delete;

	void LoadFont();


public:
	static AssetLibrary* Get();
	void Destroy();

	
	sf::Font Font;
};