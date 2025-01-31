#include "BaseRunner.h"

#include <iostream>

#include  "GameObjectManager.h"
#include "BGObject.h"
#include "TextureManager.h"
#include "TextureDisplay.h"
#include "FPSCounter.h"

/// <summary>
/// This demonstrates a running parallax background where after X seconds, a batch of assets will be streamed and loaded.
/// </summary>

const float FRAME_RATE = 60.0f;
const sf::Time BaseRunner::TIME_PER_FRAME = sf::seconds(1.0f / FRAME_RATE);
BaseRunner* BaseRunner::sharedInstance = NULL;

BaseRunner::BaseRunner() :
	window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "HO: Barrage of Threads", sf::Style::Close) {

	sharedInstance = this;
	this->window.setFramerateLimit(int(FRAME_RATE));
	
	//load initial textures
	TextureManager::getInstance()->loadFromAssetList();

	//load objects
	BGObject* bgObject = new BGObject("BGObject");
	GameObjectManager::getInstance()->addObject(bgObject);

	TextureDisplay* display = new TextureDisplay();
	GameObjectManager::getInstance()->addObject(display);

	FPSCounter* fpsCounter = new FPSCounter();
	GameObjectManager::getInstance()->addObject(fpsCounter);
}

void BaseRunner::run() {
	float MAX_FPS = 60.f;
	float MIN_THRESHOLD = 1 / MAX_FPS;

	sf::Clock clock;
	sf::Time previousTime = clock.getElapsedTime();
	sf::Time currentTime;

	sf::Time DELTA;

	//std::thread renderThread(&BaseRunner::render, this);
	//renderThread.detach();

	while (this->window.isOpen())
	{
		currentTime = clock.getElapsedTime();
		//float deltaTime = currentTime.asSeconds() - previousTime.asSeconds();
		DELTA += currentTime - previousTime;
		previousTime = currentTime;

		processEvents();

		if (DELTA > BaseRunner::TIME_PER_FRAME) {
			this->fps = 1 / DELTA.asSeconds();
			
			//update(sf::seconds(1.0f / this->fps));
			update(DELTA);
			DELTA = DELTA.Zero;
		}
		render();
	}

}

BaseRunner* BaseRunner::getInstance()
{
	return sharedInstance;
}

float BaseRunner::getFPS() const
{
	return this->fps;
}

void BaseRunner::processEvents()
{
	sf::Event event;
	if (this->window.pollEvent(event)) {
		switch (event.type) {
		
		default: GameObjectManager::getInstance()->processInput(event); break;
		case sf::Event::Closed:
			this->window.close();
			break;
		case sf::Event::KeyPressed:
			switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					this->window.close();
					break;
				default:
					break;
				}
			break;
		}
	}
}

void BaseRunner::update(sf::Time elapsedTime) {
	GameObjectManager::getInstance()->update(elapsedTime);
}

void BaseRunner::render() {
	this->window.clear();
	GameObjectManager::getInstance()->draw(&this->window);
	this->window.display();
}