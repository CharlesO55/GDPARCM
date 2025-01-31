#pragma once
#include "IETThread.h"



class IWorkerAction;
class IFinishedTask {
	virtual void onFinished(int threadID) = 0;
};

class ThreadPool : public IETThread, public IFinishedTask
{
public:
	ThreadPool(std::string name, int nWorkers);
	~ThreadPool();

	void startScehdule();
	void stopScehdule();
	void scheduleTask(IWorkerAction* action);
};

