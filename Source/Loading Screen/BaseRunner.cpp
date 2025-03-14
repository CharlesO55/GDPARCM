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
    std::this_thread::sleep_for(std::chrono::seconds(1));

    Window mainWindow;


    mainWindow.InitWindow(sf::Vector2i(1920, 1080), sf::Vector2i(3, 3));
    mainWindow.InitFPS(24);
    mainWindow.Run();

    VideoManager::Get()->Destroy();
    MusicManager::Get()->Destroy();
    AssetLibrary::Get()->Destroy();
}