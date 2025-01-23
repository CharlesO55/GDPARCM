#include <iostream>
#include <thread>


#include "MyThread.h"

void testFunc(int num = 3) {
	//std::this_thread::sleep_for(std::chrono::seconds(5));
	std::cout << "Hello from " << num << std::endl;
}

int main() {
	const int N = 1000;
	MyThread *threads[N];


	std::cout << "Main is in the house." << std::endl;

	

	for (int i = 0; i < N; i++) {
		//std::thread thread(testFunc, i);
		//thread.join();

		threads[i] = new MyThread(i);
		threads[i]->start();
	}
	
	
	std::this_thread::sleep_for(std::chrono::seconds(5));
	for (int i = 0; i < N; i++) {
		delete threads[i];
	}

	std::cout << "Main has left the house." << std::endl;


	return 0;
}

