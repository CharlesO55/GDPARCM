#include "VideoManager.h"


#include <filesystem>
#include <iostream>
#include <thread>

VideoManager* VideoManager::i = nullptr;
std::map<int, std::mutex> VideoManager::sequenceLocks;


VideoManager::VideoManager()
{
    std::cout << "Created VideoManager\n";
}

void VideoManager::Destroy()
{
    table.clear();
    delete this;
}


sf::Texture* VideoManager::TryGetFrame(int ID, int* frame)
{
    // BARRIER, WAIT FOR TO HAVE FINISHED LOADING FIRST
    VideoManager::sequenceLocks[ID].lock();
    VideoManager::sequenceLocks[ID].unlock();

    if (!table.contains(ID) || table[ID].size() < 2)
        return nullptr;

    if (*frame >= table[ID].size()) {
        *frame = 0;
    }


    sf::Texture* output = table[ID].at(*frame);
    *frame += 1;


    return output;
}


void VideoManager::RunAsync()
{
    std::thread(&VideoManager::LoadAllFolders, this).detach();
}

void VideoManager::LoadAllFolders()
{
    for (int key = 0; key < 50; key++) {
        VideoManager::sequenceLocks[key].lock();
    }

    int i = 0;
    for (const auto& folder : std::filesystem::directory_iterator(FOLDER)) {
        LoadFrames(i, folder.path().string());
        i++;
    }
}

void VideoManager::LoadFrames(int key, const std::string& folderPath)
{
    std::vector<sf::Texture*> textures;

    for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
        sf::Texture* texture = new sf::Texture();  // Dynamically allocate
        if (texture->loadFromFile(entry.path().string())) {
           textures.push_back(texture);
        }
        else {
            std::cerr << "Failed to load: " << entry.path() << std::endl;
            delete texture;  // Prevent memory leak on failure
        }
    }

    table[key] = std::move(textures);
    VideoManager::sequenceLocks[key].unlock();
}


VideoManager* VideoManager::Get()
{
    if (i == nullptr) {
        i = new VideoManager();
    }

    return i;
}