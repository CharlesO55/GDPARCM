#pragma once

#include "Command.h"

class RTImage;
class camera;
class hittable;
class ThreadPool;


class RTThread : public Command
{
private:
	int i, j;
	/*const hittable& refWorld;
	const camera& refCam;*/

	ThreadPool* pool;

	void Execute() override;

public:
	//RTThread(const camera& cam, int i, int j, const hittable& world);
	RTThread();

	void AssignPixel(int i, int j);
	void StartRTPixel(const camera& refCam, const hittable& refWorld);

	bool IsActive = false;
};