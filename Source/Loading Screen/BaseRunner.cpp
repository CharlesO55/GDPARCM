#include "BaseRunner.h"

#include "AssetLibrary.h"
#include "MusicManager.h"
#include "VideoManager.h"

#include "Window.h"



void BaseRunner::Start()
{
    AssetLibrary::Get()->LoadFont();
    MusicManager::Get()->LoadAllMusic();
    VideoManager::Get()->RunAsync();

    MusicManager::Get()->PlayMusic(MusicManager::Get()->BGM_Loading, false);

    Window mainWindow;

    const int HEIGHT = sf::VideoMode::getDesktopMode().height;
    const int WIDTH = sf::VideoMode::getDesktopMode().width;

    mainWindow.InitWindow(sf::Vector2i(WIDTH/2, HEIGHT/2), sf::Vector2i(4, 4));
    mainWindow.InitFPS(2);
    mainWindow.Run();

    VideoManager::Get()->Destroy();
    MusicManager::Get()->Destroy();
    AssetLibrary::Get()->Destroy();
}