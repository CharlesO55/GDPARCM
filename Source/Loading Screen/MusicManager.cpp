#include "MusicManager.h"

MusicManager* MusicManager::i = nullptr;


MusicManager::MusicManager()
{
    std::cout << "Created MusicManager\n";
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
	if (i == nullptr)
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

void MusicManager::StopMusic(const std::string& filename)
{
    if (table.contains(filename)) 
        table[filename]->stop();
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