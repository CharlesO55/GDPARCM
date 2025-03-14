#include "BaseRunner.h"

#include "AssetLibrary.h"
#include "MusicManager.h"
#include "VideoManager.h"

#include "Window.h"



void BaseRunner::CalcFPS()
{
    frameCount++;

    // Update FPS every 0.5 seconds
    if (fpsTimer.getElapsedTime().asSeconds() >= 0.5f) {
        fps = frameCount / fpsTimer.restart().asSeconds();
        frameCount = 0;
    }
}

void BaseRunner::Start()
{
    AssetLibrary::Get();
    MusicManager::Get();
    VideoManager::Get();

    MusicManager::Get()->PlayMusic(MusicManager::Get()->BGM_Loading, false);

    Window mainWindow;
    Window test;

    const int HEIGHT = sf::VideoMode::getDesktopMode().height;
    const int WIDTH = sf::VideoMode::getDesktopMode().width;



    mainWindow.InitWindow(sf::Vector2i(WIDTH/2, HEIGHT/2), sf::Vector2i(4, 4));
    mainWindow.InitFPS(30);

    mainWindow.Run();

    VideoManager::Get()->Destroy();
    MusicManager::Get()->Destroy();
    AssetLibrary::Get()->Destroy();
}