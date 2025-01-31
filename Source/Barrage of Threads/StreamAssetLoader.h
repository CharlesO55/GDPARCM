#pragma once
#include "IETThread.h"
class IExecutionEvent;
class StreamAssetLoader :    public IETThread
{
private:
	typedef std::string String;
	int ID;
public:
	StreamAssetLoader(String path, IExecutionEvent* executionEvent, int ID);
	~StreamAssetLoader();

private:
	void run() override;

	String path;
	IExecutionEvent* execEvent;
};

