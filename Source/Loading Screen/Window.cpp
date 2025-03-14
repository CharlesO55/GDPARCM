#include "Window.h"

#include "AssetLibrary.h"
#include "VideoManager.h"

#include <thread>

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
    UPDATE_FPS = 1.f / targetFPS;

    fpsText.setFont(AssetLibrary::Get()->Font);
    fpsText.setCharacterSize(24);
    fpsText.setFillColor(sf::Color::White);
    fpsText.setPosition(10.f, 10.f);
}

void Window::InitWindow(const sf::Vector2i& size, const sf::Vector2i& splits)
{
    m_Window = new sf::RenderWindow(sf::VideoMode(size.x, size.y), "Pootis Engage");


    const int xDimension = size.x / splits.x;
    const int yDimension = size.y / splits.y;

    for (int x = 0; x < splits.x; x++) {
        for (int y = 0; y < splits.y; y++) {
            sf::Sprite s;
            s.setTextureRect(sf::IntRect(0, 0, xDimension, yDimension));
            s.setPosition(xDimension * x, yDimension * y);
            sprites.push_back(s);
        }
    }
}


    //s->setTextureRect(sf::IntRect(pos.x, pos.y, 100, 100));
void Window::ListenInput()
{
    sf::Event event;
    while (m_Window->pollEvent(event)) {
        if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
            m_Window->close();
    }
}

Window::Window()
{
}

Window::~Window()
{
    delete m_Window;
}

void Window::Run()
{
    while (m_Window->isOpen()) {
        ListenInput();  // move listen

        /*if (CanUpdate()) {
            if (VideoManager::Get()->TryGetFrame(0, &frame, refTex)) {
                for (sf::Sprite& s : sprites) {
                    s.setTexture(refTex);
                }
            }

            Render();
        }*/
    }
}

void Window::Render()
{
    m_Window->setActive(true);
    m_Window->clear(sf::Color::Black);
    
    m_Window->draw(fpsText);

    for (const sf::Sprite s : sprites) {
        m_Window->draw(s);
    }

    m_Window->display();
}

void Window::UpdatePanel()
{

}