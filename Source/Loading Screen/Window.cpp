#include "Window.h"

#include "AssetLibrary.h"
#include "VideoManager.h"
#include "MusicManager.h"

#include <thread>

const int MAX_PERMITS = 6;

std::counting_semaphore<MAX_PERMITS> updatePermits(MAX_PERMITS);  // Correct declaration of counting_semaphore

Window::Window()
{
}

Window::~Window()
{
    delete m_Window;
}

bool Window::CanUpdate()
{
    deltaTime += clock.restart().asSeconds();

    if (deltaTime >= UPDATE_FPS) {
        fpsText.setString("FPS: " + std::to_string(static_cast<int>(1/deltaTime)));
        deltaTime = 0;
        return true;
    }

    return false;
}

void Window::InitFPS(const int targetFPS)
{
    VIDEO_FPS = 1.f / targetFPS;

    fpsText.setFont(AssetLibrary::Get()->Font);
    fpsText.setCharacterSize(24);
    fpsText.setFillColor(sf::Color::White);
    fpsText.setPosition(10.f, 10.f);
    fpsText.setOutlineColor(sf::Color::Black);
}

void Window::InitWindow(const sf::Vector2i& size, const sf::Vector2i& splits)
{
    m_Window = new sf::RenderWindow(sf::VideoMode(size.x, size.y), "Pootis Engage");


    const int xDimension = size.x / splits.x;
    const int yDimension = size.y / splits.y;

    for (int x = 0; x < splits.x; x++) {
        for (int y = 0; y < splits.y; y++) {
            sf::Sprite s;
            s.setPosition(xDimension * x, yDimension * y);
            //s.setPosition(size.x, yDimension * y);
            sprites.push_back(s);



            // Get original texture dimensions
            float originalWidth = 854;
            float originalHeight = 480;

            // Calculate the new width while keeping the aspect ratio intact
            float newHeight = 360.0f; // The target height (360p)
            float aspectRatio = originalWidth / originalHeight;
            float newWidth = newHeight * aspectRatio;

            // Scale the sprite to the new dimensions
            s.setScale(newWidth / originalWidth, newHeight / originalHeight);
        }
    }





    statusText.setFont(AssetLibrary::Get()->Font);
    statusText.setCharacterSize(30);
    statusText.setFillColor(sf::Color::White);
    statusText.setPosition(size.x / 3, size.y * 0.85);
    statusText.setOutlineColor(sf::Color::Black);

    mainScreen.setPosition(0,0);
}

void Window::OnScreenReady()
{
    VideoManager::sequenceLocks[VideoManager::Get()->TotalSequences-1].lock();
    VideoManager::sequenceLocks[VideoManager::Get()->TotalSequences-1].unlock();
    statusText.setFillColor(sf::Color::Green);
    statusText.setString("PRESS SPACE");

    completeLoading = false;
    while (!completeLoading) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }


    statusText.setString("Pootis Engage - Cen0 & DanDaDan parody - annaberu");
    MusicManager::Get()->StopMusic(MusicManager::Get()->BGM_Loading);
    MusicManager::Get()->PlayMusic(MusicManager::Get()->BGM_Finish, true);
    
    std::thread(&Window::UpdateMainPanelAsync, this).detach();
}


void Window::ListenInput()
{
    sf::Event event;
    while (m_Window->pollEvent(event)) {
        if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
            m_Window->close();
        else if (event.key.code == sf::Keyboard::Space)
            completeLoading = true;
    }
}


void Window::Run()
{
    statusText.setString("LOADING...");

    std::thread(&Window::OnScreenReady, this).detach();
    
    for (int i = 0; i < sprites.size(); i++) {
        std::thread(&Window::UpdatePanelAsync, this, i).detach();
    }

    while (m_Window->isOpen()) {
        ListenInput();  
        // RENDERS AT 60 FPS
        if (CanUpdate()) {
            Render();
        }
    }
}


void Window::UpdatePanelAsync(int i)
{
    sf::Vector2f originalPos = sprites[i].getPosition();
    originalPos.x += 100;

    int frame = 0;
    sf::Clock animationClock;
    float animationDeltaTime = 0;


    // ANIMATES AT 30 FPS
    while (m_Window->isOpen() && !completeLoading) {
        if (animationClock.getElapsedTime().asSeconds() > VIDEO_FPS) {

            // STOP UPDATING WHEN PERMIT LIMIT IS REACHED
            if (frame == 0)
                updatePermits.acquire();

            animationClock.restart();
            // LOCK IS CALLED BY VIDEO MANAGER
            sf::Texture* tex = VideoManager::Get()->TryGetFrame(i, &frame);
            if (tex)
                sprites[i].setTexture(*tex);

            /*sprites[i].move(sf::Vector2f(-10, 0));
            if (sprites[i].getPosition().x < -400) {
                sprites[i].setPosition(originalPos);
            }*/

            // ON ANIM FINISH, LET OTHERS HAVE A CHANCE 
            if (frame == 0) {
                updatePermits.release();
                std::cout << "Sleep";
                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
        }
    }
}

void Window::UpdateMainPanelAsync()
{
    int frame = 0;
    sf::Clock animationClock;
    float animationDeltaTime = 0;


    // ANIMATES AT 30 FPS
    while (m_Window->isOpen()) {
        if (animationClock.getElapsedTime().asSeconds() > VIDEO_FPS) {
            animationClock.restart();

            // LOCK IS CALLED BY VIDEO MANAGER
            sf::Texture* tex = VideoManager::Get()->TryGetFrame(VideoManager::Get()->TotalSequences - 1, &frame);
            if (tex)
                mainScreen.setTexture(*tex);
        }
    }
}



void Window::Render()
{
    m_Window->setActive(true);
    m_Window->clear(sf::Color::Black);
    
    if (!completeLoading) {
        for (const sf::Sprite s : sprites) {
            m_Window->draw(s);
        }
    }
    else {
        m_Window->draw(mainScreen);
    }

    m_Window->draw(fpsText);
    m_Window->draw(statusText);
    m_Window->display();
}