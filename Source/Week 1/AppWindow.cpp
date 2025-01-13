#include "AppWindow.h"

#include "Debugger.h"
#include "ImageLoader.h"
#include "EngineTime.h"


void AppWindow::Init()
{
    m_Window = new sf::RenderWindow(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "GDPARCM");
    Debugger::Print("[Init] AppWindow", EnumMsg::SUCCESS);

    m_HUD_FPS = new AText("FPS: _");
    m_HUD_FPS->Init();
}

bool AppWindow::Run()
{
    HandleInput();

    if (EngineTime::IsTick()) {
        ImageLoader::Update();
        
        m_Window->clear();
        ImageLoader::Draw(*m_Window, WINDOW_SIZE);
        
        m_HUD_FPS->SetTextContent("FPS: " + std::to_string(EngineTime::GetFPS()));
        m_HUD_FPS->Draw(*m_Window);

        
        m_Window->display();
    }


    return m_Window->isOpen();
}

void AppWindow::HandleInput()
{
    sf::Event event;
    while (m_Window->pollEvent(event))
    {
        switch (event.type) {
        
        case sf::Event::Closed:
            m_Window->close();
            break;
        
        case sf::Event::Resized:
            this->WINDOW_SIZE = m_Window->getSize();
            break;

        case sf::Event::KeyPressed:
            switch (event.key.code) {
            case sf::Keyboard::Escape:
                m_Window->close();
                break;
            default:
                break;
            }
            break;
        
        default:
            break;
        }
    }
}

void AppWindow::Close()
{
    delete m_Window;

    Debugger::Print("[Close] AppWindow", EnumMsg::SUCCESS);
}