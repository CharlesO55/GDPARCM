#include "StreamAssetLoader.h"
#include <iostream>
#include <random>

#include "TextureManager.h"
#include "StringUtils.h"
#include "IExecutionEvent.h"



StreamAssetLoader::StreamAssetLoader(String path, IExecutionEvent* executionEvent, int ID)
{
	this->path = path;
	AddListener(executionEvent);
	this->ID = ID;
}

StreamAssetLoader::~StreamAssetLoader()
{
	std::cout << "DESTROY " << ID << ".\n";
}

void StreamAssetLoader::AddListener(IExecutionEvent* executionEvent)
{
	this->onFinishDelegates.push_back(executionEvent);
}

void StreamAssetLoader::run()
{
	this->isRunning = true;

	std::cout << "START " << ID << ".\n";

	//simulate loading of very large file
	std::random_device seeder;
	std::mt19937 engine(seeder());
	std::uniform_int_distribution<int> dist(1000, 4000);
	IETThread::sleep(dist(engine));
	//IETThread::sleep(1000);

	std::vector<String> tokens = StringUtils::split(path, '/');
	String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];


	std::cout << "LOADING " << ID << ".\n";
	TextureManager::getInstance()->instantiateAsTexture(path, assetName, true);

	//std::cout << "[TextureManager] Loaded streaming texture: " << assetName << std::endl;
	

	for (auto e : this->onFinishDelegates) {
		e->onFinishedExecution();
	}

	//delete after being done
	//delete this;


	// DONT DELETE. WE CHECK THE VALUE
	this->isRunning = false;

}