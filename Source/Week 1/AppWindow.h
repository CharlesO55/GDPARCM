#pragma once

#include <SFML/Graphics.hpp>

#include "AText.h"

class AppWindow {
private:
	sf::Vector2u WINDOW_SIZE = sf::Vector2u(1920, 1080);
	sf::RenderWindow *m_Window;
	
	AText* m_HUD_FPS;

public:
	void Init();
	void Close();
	bool Run();
	void HandleInput();
};