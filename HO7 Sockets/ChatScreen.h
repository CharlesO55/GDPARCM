#pragma once
#include <memory>

#include "AUIScreen.h"
#include "EventBroadcaster.h"
#include "imgui.h"

class ChatScreen :    public AUIScreen, Observer
{

public:
	enum Source
	{
		SERVER,
		CLIENT
	};

private:
	ChatScreen();
	~ChatScreen();

	void drawUI() override;
	friend class UIManager;

	std::unique_ptr<ImGuiTextBuffer> textLog;
	int lineCount = 0;
	char textToSend[1024 * 16] = "";

	void appendText(String text, Source source);
	void onTriggeredEvent(std::string eventName, std::shared_ptr<Parameters> parameters) override;
};

