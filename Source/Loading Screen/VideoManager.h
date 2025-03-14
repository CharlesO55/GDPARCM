#pragma once
#include "Dependencies.h"

class VideoManager
{
private:
	const std::string FOLDER = "Resources/Images/";


	static VideoManager* i;

	VideoManager();
	VideoManager(const VideoManager&) = delete;
	VideoManager& operator=(const VideoManager&) = delete;


private:
	void LoadAllFolders();
	void LoadFrames(int i, const std::string& folderPath);

public:
	std::map<int, std::vector<sf::Texture>> table;
	static VideoManager* Get();
	void Destroy();

	const std::vector<sf::Texture>& GetFrames(int i);
	
	const bool TryGetFrame(int ID, int* frame, sf::Texture& output);
};