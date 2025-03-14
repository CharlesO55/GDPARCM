#pragma once
#include "Dependencies.h"

class MusicManager
{
public:
	const std::string BGM_Loading = "Menace.wav";
	const std::string BGM_Finish = "killdeer.wav";

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
	void PlayMusic(const std::string& filename, bool loop);


};