#include "VideoManager.h"

#include <filesystem>
VideoManager* VideoManager::i = NULL;


VideoManager::VideoManager()
{
    LoadAllFolders();
}

void VideoManager::Destroy()
{
    table.clear();
    delete this;
}

const std::vector<sf::Texture>& VideoManager::GetFrames(int i)
{
    return table[i];
}

const bool VideoManager::TryGetFrame(int ID, int* frame, sf::Texture& output)
{
    if (!table.contains(ID) || table[ID].size() < 2)
        return false;
    
    if (*frame >= table[ID].size()) {
        *frame = 0;
    }
    output = table[ID].at(*frame);
    *frame += 1;
    
    return true;
}

void VideoManager::LoadAllFolders()
{
    int i = 0;
    for (const auto& folder : std::filesystem::directory_iterator(FOLDER)) {
        std::thread(&VideoManager::LoadFrames, this, i, folder.path().string()).detach();
        i++;
    }
}

void VideoManager::LoadFrames(int i, const std::string& folderPath)
{
    for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
        std::cout << entry.path();
        
        sf::Texture texture;
        if (texture.loadFromFile(entry.path().string())) {
            std::cout << entry.path().string() << std::endl;

            //VideoManager::Get()->table[i].push_back(std::move(texture));
        }
        else {
            std::cerr << "Failed to load: " << entry.path() << std::endl;
        }
    }
}


        //LoadFrames(i, entry.path().string());

//if (false) {}//(entry.path().string() == FOLDER+"_") {}

VideoManager* VideoManager::Get()
{
    if (i == NULL)
        i = new VideoManager();

    return i;
}