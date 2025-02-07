#include "ThreadPool.h"
#include "RTThread.h"

#include <thread>


void ThreadPool::Update()
{
	while (isActive) {
		if (!WaitingQueue.empty()) {
			for (RTThread* thread : ActiveWorkers) {
				if (!thread->IsActive) {
					thread->AssignPixel(WaitingQueue.front().i, WaitingQueue.front().j);
					WaitingQueue.pop();

					thread->StartRTPixel(this->refCam, this->refWorld);
					break;
				}
			}
		}
	}
}

ThreadPool::ThreadPool(const camera& cam, const hittable& world)
	: refCam(cam), refWorld(world)
{
}

void ThreadPool::InitThreadList(int nThreads)
{
	this->nThreads = nThreads;
	for (int i = 0; i < nThreads; i++) {
		this->ActiveWorkers.push_back(new RTThread());
	}
}

void ThreadPool::Add(RTParams params)
{
	this->WaitingQueue.push(params);
}

void ThreadPool::StartProcessing()
{
	isActive = true;
	std::thread UpdateThread(&ThreadPool::Update, this);
	UpdateThread.detach();
}

void ThreadPool::Stop()
{
	isActive = false;
}