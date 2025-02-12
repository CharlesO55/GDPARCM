#pragma once
#include "IETThread.h"


#include <mutex>
#include <queue>
//class IWorkerAction;
class IFinishedTask {
	virtual void onFinished(int threadID) = 0;
};

class ThreadPool : public IETThread//, public IFinishedTask
{
private:
	std::queue<IETThread*> waitingQueue;
	bool isRunning = false;

	int nWorkers;

	std::mutex queueLock;

public:
	ThreadPool(int nWorkers);
	~ThreadPool();

	void startSchedule();
	void stopSchedule();
	void scheduleTask(IETThread* action);

	void run() override;
};