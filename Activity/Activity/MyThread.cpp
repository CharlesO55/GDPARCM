#include "MyThread.h"

#include <thread>
#include <iostream>

bool MyThread::isRun()
{
	return run;
}

MyThread::MyThread(int id) : num(id)
{
}

MyThread::~MyThread()
{
}

void MyThread::start() {
	std::thread(&MyThread::run, this).detach();
}

void MyThread::sleep(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void MyThread::run(MyThread* thread)
{
	while (thread->isRun()) {
		std::cout << "Thread #" << num << std::endl;
		this->sleep(100);
	}
}