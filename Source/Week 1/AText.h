#pragma once
#include "Asset.h"

#include "EnumFonts.h"
class AText : public Asset
{
private:
	sf::Font m_Font;
	sf::Text m_Text;

	std::string m_Content;

public:
	AText(const std::string text, const std::string fontFile = FILEPATH_FONT_DEFAULT);

	void Init();
	void Destroy();

	sf::Drawable& GetDrawable();

	void SetTextContent(std::string content);
};