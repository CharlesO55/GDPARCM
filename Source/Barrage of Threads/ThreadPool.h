#pragma once
#include "StreamAssetLoader.h"

#include <vector>
#include <mutex>
#include <queue>

class IFinishedTask {
	virtual void onFinished(int threadID) = 0;
};

class ThreadPool : public IETThread//, public IFinishedTask
{
private:
	std::vector<StreamAssetLoader*> workers;
	std::queue<StreamAssetLoader*> waitingQueue;
	
	std::mutex queueLock;
	
	int nWorkers;
	int FindInactiveSlot();

public:
	ThreadPool(int nWorkers);
	~ThreadPool();

	void startSchedule();
	void stopSchedule();
	void scheduleTask(StreamAssetLoader* action);

	void run() override;
};