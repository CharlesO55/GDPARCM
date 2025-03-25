#include "ChatScreen.h"
#include <sstream>

#include "NetworkManager.h"

void ChatScreen::appendText(String text, Source source)
{
	std::string sourceStr = "SERVER";
	if(source == CLIENT)
	{
		sourceStr = "CLIENT";
	}
	std::stringstream buffer;
	buffer << this->lineCount << sourceStr << " : " << text << std::endl;

	this->textLog->appendf(buffer.str().c_str());
	this->lineCount++;
}

ChatScreen::ChatScreen() : AUIScreen("ChatScreen")
{
	this->textLog = std::make_unique<ImGuiTextBuffer>();
	EventBroadcaster::getInstance()->addObserver(EventNames::ON_RECEIVED_MSG, this);
}

ChatScreen::~ChatScreen()
{
	EventBroadcaster::getInstance()->removeObserver(EventNames::ON_RECEIVED_MSG);
}

void ChatScreen::drawUI()
{
	ImGui::Begin("Chat Main window");                          // Create a window called "Hello, world!" and append into it.

	static ImGuiInputTextFlags flags = ImGuiInputTextFlags_AllowTabInput | ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CtrlEnterForNewLine | ImGuiInputTextFlags_AlwaysOverwrite;
	ImGui::InputTextMultiline("Chatbox", textToSend, IM_ARRAYSIZE(textToSend), ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 16), flags);

	if(NetworkManager::getInstance()->getServerState() == NetworkManager::CLIENTS_CONNECTED || NetworkManager::getInstance()->getClientState() == NetworkManager::ClientState::CONNECTED_TO_SERVER)
	{
		if(ImGui::Button("Send"))
		{
			//send message
			if(NetworkManager::getInstance()->getEntityType() == NetworkManager::SERVER)
			{
				NetworkManager::getInstance()->sendMessageAsServer(textToSend);
			}
			else
			{
				NetworkManager::getInstance()->sendMessageAsClient(textToSend);
			}
			
		}
	}
	else
	{
		ImGui::Text("Establish connection to server/client first.");
	}

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	ImGui::End();

	ImGui::Begin("Chat Response");
	if (ImGui::Button("Clear")) { this->textLog->clear(); this->lineCount = 0; }
	ImGui::TextUnformatted(this->textLog->begin(), this->textLog->end());
	ImGui::End();
}

void ChatScreen::onTriggeredEvent(std::string eventName, std::shared_ptr<Parameters> parameters)
{
	if(eventName == EventNames::ON_RECEIVED_MSG)
	{
		String msgString = parameters->getStringData(ParameterKeys::MSG_KEY, "");
		int sourceKey = parameters->getIntData(ParameterKeys::SOURCE_KEY, 0);
		Source source = Source::SERVER;
		if(sourceKey == 1)
		{
			source = Source::CLIENT;
		}

		this->appendText(msgString, source);
	}
}
