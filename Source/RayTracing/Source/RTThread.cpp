#include "RTThread.h"

#include "camera.h"
#include "hittable.h"

#include <thread>
#include "ThreadPool.h"


void RTThread::Execute()
{
	//pool->RemoveFinishedThread(this);
	//std::cout << "Done";
	////delete this;

	IsActive = false;
}

//RTThread::RTThread(const camera& cam, int i, int j, const hittable& world) :
//	refWorld(world),
//	refCam(cam)
//{
//	this->i = i;
//	this->j = j;
//}

RTThread::RTThread()
{

}

void RTThread::AssignPixel(int i, int j)
{
	this->i = i;
	this->j = j;
}

void RTThread::StartRTPixel(const camera& refCam, const hittable& refWorld)
{
	IsActive = true;

	std::thread thread(&camera::ComputePixel, refCam, i, j, std::ref(refWorld), this);
	thread.detach();
}