#include "AssetLibrary.h"

AssetLibrary* AssetLibrary::i = NULL;


AssetLibrary::AssetLibrary()
{
	LoadFont();
}

void AssetLibrary::LoadFont()
{
	if (!Font.loadFromFile("Resources/Font/animeace.ttf")) {
		std::cerr << "Failed to load font!\n";
		return;
	}
}

AssetLibrary* AssetLibrary::Get()
{
	if (i == NULL)
		i = new AssetLibrary();

	return i;
}

void AssetLibrary::Destroy()
{
	delete this;
}
