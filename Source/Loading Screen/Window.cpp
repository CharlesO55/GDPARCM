#include "Window.h"

#include "AssetLibrary.h"
#include "VideoManager.h"
#include "MusicManager.h"

#include <thread>

const int MAX_PERMITS = 7;

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
    m_Window = new sf::RenderWindow(sf::VideoMode(size.x, size.y), "Pootis Engage (60fps render, 30fps animate) ");

    const int xDimension = size.x / splits.x;
    const int yDimension = size.y / splits.y;

    for (int x = 0; x < splits.x; x++) {
        for (int y = 0; y < splits.y; y++) {
            sf::Sprite s;
            s.setPosition(xDimension * x, yDimension * y);
            s.setScale(0.5f, 0.5f);
            sprites.push_back(s);
        }
    }

    statusText.setFont(AssetLibrary::Get()->Font);
    statusText.setCharacterSize(30);
    statusText.setFillColor(sf::Color::White);
    statusText.setPosition(size.x / 3, size.y * 0.85);
    statusText.setOutlineColor(sf::Color::Black);
    
    mainScreen = new sf::Sprite();
    mainScreen->setPosition(0,0);
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
    
    // ADD SOME MORE BIG ONES
    int bigPanels = 2;
    for (int i = 0; i < bigPanels; i++) {
        sprites.push_back(sf::Sprite());
        sprites.back().setPosition(1920, 1080/2 * i);
    }

    for (int i = 0; i < sprites.size() - bigPanels ; i++) {
        std::thread(&Window::UpdatePanelAsync, this, i).detach();
    }

    for (int i = 1; i <= bigPanels; i++) {
        std::thread(&Window::UpdateBigPanelAsync, this, sprites.size() - i).detach();
    }

    while (m_Window->isOpen()) {
        ListenInput();  
        // RENDERS AT 60 FPS
        if (CanUpdate()) {
            Render();
        }
    }
}


void Window::UpdatePanelAsync(int index)
{
    int frame = 1;
    sf::Clock animationClock;
    float animationDeltaTime = 0;

    // ANIMATES AT 30 FPS
    while (m_Window->isOpen() && !completeLoading) {
        if (animationClock.getElapsedTime().asSeconds() > VIDEO_FPS) {

            // STOP UPDATING WHEN PERMIT LIMIT IS REACHED
            if (frame == 1) {
                updatePermits.acquire();
            }

            animationClock.restart();
            // LOCK IS CALLED BY VIDEO MANAGER
            sf::Texture* tex = VideoManager::Get()->TryGetFrame(index, &frame);
            if (tex) {
                sprites[index].setTexture(*tex);
                frame++;
            }

            if (frame == 1) {
                updatePermits.release();
            }
        }
    }
}

void Window::UpdateBigPanelAsync(int index)
{
    sf::Vector2f originalPos = sprites[index].getPosition();

    int frame = 1;
    sf::Clock animationClock;
    float animationDeltaTime = 0;

    int permitsReq = 2;

    // ANIMATES AT 30 FPS
    while (m_Window->isOpen() && !completeLoading) {
        if (animationClock.getElapsedTime().asSeconds() > VIDEO_FPS) {
            sf::Vector2f pos = sprites[index].getPosition();

            // STOP UPDATING WHEN PERMIT LIMIT IS REACHED
            if (originalPos.x == pos.x) {
                for (int i = 0; i < permitsReq; i++) {
                    updatePermits.acquire();
                }
            }

            animationClock.restart();
            // LOCK IS CALLED BY VIDEO MANAGER
            sf::Texture* tex = VideoManager::Get()->TryGetFrame(index, &frame);
            if (tex) {
                sprites[index].setTexture(*tex);
                frame++;
            }

            if (sprites[index].getPosition().x < -800) {
                updatePermits.release(permitsReq);
                sprites[index].setPosition(originalPos);
            }
            else {
                sprites[index].move(-20, 0);
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
            if (tex) {
                mainScreen->setTexture(*tex);
                frame++;
            }
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
        m_Window->draw(*mainScreen);
    }

    m_Window->draw(fpsText);
    m_Window->draw(statusText);
    m_Window->display();
}