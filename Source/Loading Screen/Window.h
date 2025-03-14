#pragma once
#include "Dependencies.h"

class Window
{
	sf::RenderWindow* m_Window;
	sf::Text fpsText;
	sf::Texture* refTex;

	sf::Clock clock;
	float fps = 0.0f;

	float VIDEO_FPS = 1.f / 30;
	const float UPDATE_FPS = 1.f / 60;
	float deltaTime;

	std::vector<sf::Sprite> sprites;

	

private:
	bool CanUpdate();
	void ListenInput();
	void Render();

	void UpdatePanelAsync(int i /*,sf::Sprite* s*/);

public:
	void InitFPS(const int targetFPS = 30);
	void InitWindow(const sf::Vector2i& size, const sf::Vector2i& splits);
	
	void OnScreenReady();

public:
	Window();
	~Window();

	void Run();
};