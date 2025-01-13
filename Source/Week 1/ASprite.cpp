#include "ASprite.h"

#include "Debugger.h"

ASprite::ASprite(std::string filepath, sf::IntRect size, bool repeatTex) : Asset(filepath), 
    m_Size(size),
    m_RepeatTex(repeatTex)
{
}

ASprite::~ASprite()
{
    Destroy();
}

void ASprite::Destroy()
{
}

void ASprite::Init()
{
    if (m_Tex.loadFromFile(m_Path)) {
        m_Tex.setRepeated(m_RepeatTex);
        m_Sprite.setTextureRect(m_Size);
        m_Sprite.setTexture(m_Tex);
    }
    else
        Debugger::Print("[Init] Image", EnumMsg::ERROR);
}




sf::Drawable& ASprite::GetDrawable()
{
    return m_Sprite;
}

sf::Sprite& ASprite::GetSprite()
{
    return m_Sprite;
}