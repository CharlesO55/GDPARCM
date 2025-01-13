#pragma once

#include <SFML/System.hpp>

class EngineTime
{
private:
	static EngineTime* i;
	
	sf::Clock m_Clock;

	float m_DeltaTime = 0;
	float m_FPS = 0;
	bool m_Tick = false;

public:
	static void Init();
	static void Update();
	static void Destroy();


	static bool IsTick();
	static const float GetDelta();
	static const float GetFPS();
};