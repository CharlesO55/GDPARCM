#include "StreamAssetLoader.h"
#include <iostream>
#include <random>

#include "TextureManager.h"
#include "StringUtils.h"
#include "IExecutionEvent.h"



StreamAssetLoader::StreamAssetLoader(String path, IExecutionEvent* executionEvent, int ID)
{
	this->path = path;
	this->execEvent = executionEvent;
	this->ID = ID;
}

StreamAssetLoader::~StreamAssetLoader()
{
	std::cout << "DESTROY " << ID << ".\n";
}

void StreamAssetLoader::run()
{
	std::cout << "START " << ID << ".\n";

	//simulate loading of very large file
	std::random_device seeder;
	std::mt19937 engine(seeder());
	std::uniform_int_distribution<int> dist(1000, 4000);
	IETThread::sleep(dist(engine));

	std::vector<String> tokens = StringUtils::split(path, '/');
	String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];



	std::cout << "LOADING " << ID << ".\n";
	TextureManager::getInstance()->instantiateAsTexture(path, assetName, true);

	//std::cout << "[TextureManager] Loaded streaming texture: " << assetName << std::endl;
	
	if (this->execEvent != NULL)
		this->execEvent->onFinishedExecution();
	
	//delete after being done
	delete this;
}