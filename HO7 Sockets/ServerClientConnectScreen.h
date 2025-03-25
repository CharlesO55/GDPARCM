#pragma once
#include "AUIScreen.h"
class ServerClientConnectScreen :    public AUIScreen
{
public:
	void appendText(String text);

private:
	ServerClientConnectScreen();
	~ServerClientConnectScreen() = default;

	virtual void drawUI() override;
	friend class UIManager;
	
};

