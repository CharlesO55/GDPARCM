#pragma once

#include <SFML/Graphics.hpp>

class Asset
{
protected:
	std::string m_Path;

public:
	Asset(std::string filepath);


	virtual void Init() = 0;
	virtual void Destroy() = 0;

	virtual sf::Drawable& GetDrawable() = 0;
	

	virtual void Draw(sf::RenderTarget& target) {
		target.draw(GetDrawable());
	}
};