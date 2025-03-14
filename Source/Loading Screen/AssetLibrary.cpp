#include "AssetLibrary.h"

AssetLibrary* AssetLibrary::i = nullptr;


AssetLibrary::AssetLibrary()
{
	std::cout << "Created AssetLibrary\n";
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
	if (i == nullptr)
		i = new AssetLibrary();

	return i;
}

void AssetLibrary::Destroy()
{
	delete this;
}