#include "ImageLoader.h"

#include "Debugger.h"
#include "EngineTime.h"
#include <filesystem>

ImageLoader* ImageLoader::i = NULL;



void ImageLoader::Init()
{
    if (i != NULL) {
        Debugger::Print("[Duplicate] ImageLoader", EnumMsg::WARNING);
        return;
    }

    i = new ImageLoader();

    // LOAD BACKGROUND IMAGE FIRST
    i->m_BGImage = new ASprite(i->BACKGROUND_FILEPATH, sf::IntRect(0, 0, 1920, 1080 * 2), true);
    i->m_BGImage->Init();

    // PREP OTHER ICON FILENAMES
    for (const auto& file : std::filesystem::directory_iterator(i->STREAMING_FOLDER)) {
        if (std::filesystem::is_regular_file(file)) {
            i->m_Filenames.push_back(file.path().filename().string());
        }
    }

    Debugger::Print("[Init] ImageLoader", EnumMsg::SUCCESS);
}

void ImageLoader::Update()
{
    static float Time = 0;
    Time += EngineTime::GetDelta();


    if (Time > 1 && i->m_Images.size() < i->m_Filenames.size()) {
        Time = 0;

        int index = i->m_Images.size();

        //PATH
        std::string fullpath = i->STREAMING_FOLDER + i->m_Filenames[index];
        
        //SIZE
        int OFFSET = 100;
        int ICON_SIZE = 64;
        
        //POSITION
        sf::Vector2f pos(
            (index % 19)* OFFSET,
            index / 19 * OFFSET
        );

        //CREATE ASSET
        ASprite* icon = new ASprite(fullpath, sf::IntRect(0, 0, ICON_SIZE, ICON_SIZE));
        icon->Init();
        icon->GetSprite().move(pos);

        i->m_Images.push_back(icon);
    }
}

void ImageLoader::Draw(sf::RenderTarget& target, const sf::Vector2u WINDOW_SIZE)
{
    // MOVE BG
    sf::Sprite& sprite = i->m_BGImage->GetSprite();
    sprite.move(sf::Vector2f(0, -1.f));

    if (-sprite.getPosition().y > WINDOW_SIZE.y) {
        sprite.setPosition(0, 0);
    }

    // DRAW BG
    i->m_BGImage->Draw(target);

    // DRAW ICONS
    for (ASprite* icon : i->m_Images) {
        icon->Draw(target);
    }
}

void ImageLoader::Destroy()
{
    Debugger::Print("[Destroy] ImageLoader", EnumMsg::WARNING);
}