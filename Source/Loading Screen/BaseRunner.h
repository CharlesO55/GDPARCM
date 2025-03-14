#pragma once


#include "Dependencies.h"


class BaseRunner
{
	sf::Clock clock;
	sf::Clock fpsTimer;
	int frameCount = 0;
	float fps = 0.0f;

	void CalcFPS();

public:
	void Start();
};