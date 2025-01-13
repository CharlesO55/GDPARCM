#pragma once
#include "Asset.h"


class ASprite : public Asset
{
private:
	sf::IntRect m_Size;
	sf::Texture m_Tex;
	sf::Sprite m_Sprite;
	bool m_RepeatTex;

public:
	ASprite(const std::string filepath, const sf::IntRect size, const bool repeatTex = false);
	~ASprite();

	void Init();
	void Destroy();

	sf::Drawable& GetDrawable();
	sf::Sprite& GetSprite();
};