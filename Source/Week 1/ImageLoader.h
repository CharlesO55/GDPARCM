#pragma once

#include "ASprite.h"

class ImageLoader{
private:
	static ImageLoader* i;

	const std::string BACKGROUND_FILEPATH = "../Media/Textures/Desert.png";
	const std::string STREAMING_FOLDER = "../Media/Streaming/";

	std::vector<std::string> m_Filenames;

public:
	ASprite* m_BGImage;
	std::vector<ASprite*> m_Images;

	static void Init();
	static void Update();
	static void Draw(sf::RenderTarget& target, const sf::Vector2u WINDOW_SIZE);
	static void Destroy();
};