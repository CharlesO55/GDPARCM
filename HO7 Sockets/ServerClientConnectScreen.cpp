#include "ServerClientConnectScreen.h"
#include "imgui.h"
#include "NetworkManager.h"

ServerClientConnectScreen::ServerClientConnectScreen(): AUIScreen("ServerClientConnectScreen")
{
}

void ServerClientConnectScreen::drawUI()
{
    ImGui::Begin("Server-Client Connect");

    NetworkManager::ServerState serverState = NetworkManager::getInstance()->getServerState();

    if(serverState == NetworkManager::ServerState::SERVER_INACTIVE)
    {
        if (ImGui::Button("Start as Server"))
        {
            NetworkManager::getInstance()->serverStart();
        }
    }
    else if(serverState == NetworkManager::ServerState::WAITING_CONNECTION)
    {
        ImGui::Text("Waiting for incoming clients to connect...");
    }

    else if (serverState == NetworkManager::ServerState::CLIENTS_CONNECTED)
    {
        ImGui::Text("Connected to client!");
    }
   
    ImGui::SameLine();

    NetworkManager::ClientState clientState = NetworkManager::getInstance()->getClientState();
    if (clientState == NetworkManager::ClientState::CLIENT_INACTIVE)
    {
        if (ImGui::Button("Connect to Server"))
        {
            NetworkManager::getInstance()->clientStart();
        }
    }
    else if (clientState == NetworkManager::ClientState::ATTEMPTING_SERVER_CONNECT)
    {
        ImGui::Text("Attempting to connect to a server...");
    }

    else if(clientState == NetworkManager::ClientState::CONNECTED_TO_SERVER)
    {
        ImGui::Text("Connected to server!");
    }

    ImGui::End();
}
