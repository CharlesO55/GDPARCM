#include "MusicManager.h"

MusicManager* MusicManager::i = NULL;


MusicManager::MusicManager()
{
    LoadAllMusic();
}

void MusicManager::Destroy()
{
    for (auto& pair : table) {
        pair.second->stop();
        delete pair.second; 
    }
    table.clear();
    
    delete this;
}

MusicManager* MusicManager::Get()
{
	if (i == NULL)
		i = new MusicManager();

	return i;
}

void MusicManager::LoadMusic(const std::string& filename)
{
    sf::Music* music = new sf::Music();
    if (!music->openFromFile(FOLDER + filename)) {
        std::cerr << FOLDER + filename;
        
        delete music;
        return;
    }

    table[filename] = music;
}

void MusicManager::LoadAllMusic()
{
    LoadMusic(BGM_Loading);
    LoadMusic(BGM_Finish);
}

void MusicManager::PlayMusic(const std::string& filename, bool loop)
{
    if (table.contains(filename)) {
        table[filename]->play();
        table[filename]->setLoop(loop);
    }
    else {
        std::cerr << filename;
    }
}