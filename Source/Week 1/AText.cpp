#include "AText.h"

#include "Debugger.h"


AText::AText(const std::string text, const std::string fontFile) : Asset(fontFile), m_Content(text)
{
}

void AText::Init()
{
	if (!m_Font.loadFromFile(m_Path))
	{
		Debugger::Print("[Init] Font", EnumMsg::ERROR);
	}

	m_Text = sf::Text(m_Content, m_Font);
}

void AText::Destroy()
{
}

sf::Drawable& AText::GetDrawable()
{
	return m_Text;
}

void AText::SetTextContent(std::string content)
{
	m_Text.setString(content);
}
