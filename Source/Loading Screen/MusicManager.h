#pragma once
#include "Dependencies.h"

class MusicManager
{
public:
	const std::string BGM_Loading = "Absolute Territory.wav";
	const std::string BGM_Finish = "DanDaDan.wav";

private:
	const std::string FOLDER = "Resources/Audio/";


	static MusicManager* i;

	MusicManager();
	MusicManager(const MusicManager&) = delete;
	MusicManager& operator=(const MusicManager&) = delete;

	std::unordered_map<std::string, sf::Music*> table;


private:
	void LoadMusic(const std::string& filename);

public:
	static MusicManager* Get();
	void Destroy();
	
	
	void LoadAllMusic();
	void StopMusic(const std::string& filename);
	void PlayMusic(const std::string& filename, bool loop);


};