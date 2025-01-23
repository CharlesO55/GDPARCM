#pragma once
class MyThread
{
public:
	bool run = false;
	int num;

	bool isRun();

public:
	MyThread(int id);
	virtual ~MyThread();

	void start();
	static void sleep(int ms);



protected:
	virtual void run(MyThread* thread);
};