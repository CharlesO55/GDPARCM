#pragma once
//#include "Dependencies.h"
#include <SFML/Graphics.hpp>
#include <map>
#include <mutex>


class VideoManager
{
private:
	const std::string FOLDER = "Resources/Images/";

	std::map<int, std::vector<sf::Texture*>> table;


	static VideoManager* i;
	


	VideoManager();
	VideoManager(const VideoManager&) = delete;
	VideoManager& operator=(const VideoManager&) = delete;


private:
	void LoadFrames(int i, const std::string& folderPath);
	void LoadAllFolders();

public:
	static VideoManager* Get();
	void Destroy();
	void RunAsync();

	sf::Texture* TryGetFrame(int ID, int* frame);
	static std::map<int, std::mutex> sequenceLocks;
};