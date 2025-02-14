#pragma once
#include "IETThread.h"
#include <vector>

class IExecutionEvent;

class StreamAssetLoader :    public IETThread
{
private:
	typedef std::string String;
	int ID;
public:
	StreamAssetLoader(String path, IExecutionEvent* executionEvent, int ID);
	~StreamAssetLoader();

	void AddListener(IExecutionEvent* executionEvent);

private:
	void run() override;

	String path;
	std::vector<IExecutionEvent*> onFinishDelegates;
};