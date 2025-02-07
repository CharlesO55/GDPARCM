#pragma once
#include <queue>
#include <vector>

#include "vec3.h"
#include "RTParams.h"

class RTThread;
class hittable;
class camera;


class ThreadPool
{
private:
	int nThreads;

	//std::queue<RTThread*>	WaitingQueue;
	std::queue<RTParams>	WaitingQueue;
	std::vector<RTThread*>  ActiveWorkers;

	void Update();

	const hittable& refWorld;
	const camera& refCam;

	bool isActive = false;

public:
	ThreadPool(const camera& cam, const hittable& world);

	void InitThreadList(int nThreads);
	void Add(RTParams params);
	void StartProcessing();
	void Stop();
};