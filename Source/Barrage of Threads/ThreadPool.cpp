#include "ThreadPool.h"

int ThreadPool::FindInactiveSlot()
{
	if (workers.size() < nWorkers)
		return -1;

	for (int i = 0; i < nWorkers; i++) {
		if (!workers[i]->IsRunning())
			return i;
	}

	return -2;
}

ThreadPool::ThreadPool(int nWorkers)
{
	this->nWorkers = nWorkers;
}

ThreadPool::~ThreadPool()
{
}

void ThreadPool::startSchedule()
{
	isRunning = true;
	std::thread scheduleThread(&ThreadPool::run, this);
	scheduleThread.detach();
}

void ThreadPool::stopSchedule()
{
	isRunning = false;
}

void ThreadPool::scheduleTask(StreamAssetLoader* action)
{
	queueLock.lock();
	this->waitingQueue.push(action);
	queueLock.unlock();
}

void ThreadPool::run()
{
	while (this->isRunning) {
		if (!waitingQueue.empty()) {
			int i = FindInactiveSlot();
			
			//std::cout << i << std::endl;

			if (i == -2) {} // NO  SLOTS
			else if (i == -1) {
				// THERE IS STILL NULL
				queueLock.lock();
				
				workers.push_back(this->waitingQueue.front());
				this->waitingQueue.front()->start();
				this->waitingQueue.pop();
				
				queueLock.unlock();
			}
			else {
				// REPLACE AN EXISTING
				queueLock.lock();

				delete workers[i];

				workers[i] = this->waitingQueue.front();
				workers[i]->start();
				this->waitingQueue.pop();

				queueLock.unlock();
			}
		}
	}
}