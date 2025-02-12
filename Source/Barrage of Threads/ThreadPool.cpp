#include "ThreadPool.h"

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

void ThreadPool::scheduleTask(IETThread* action)
{
	queueLock.lock();
	this->waitingQueue.push(action);
	queueLock.unlock();
}

void ThreadPool::run()
{
	while (this->isRunning) {
		if (!waitingQueue.empty() /*&& nWorkers > 0*/)
		{
			queueLock.lock();

			this->waitingQueue.front()->start();
			this->waitingQueue.pop();
		
			queueLock.unlock();
		}
	}
}