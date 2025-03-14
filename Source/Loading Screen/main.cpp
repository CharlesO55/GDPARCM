
#include "BaseRunner.h"



/*class A {
	int i = 0;

public:
	static std::mutex Lock;
	A(int i) { this->i = i; }
	static std::map<int, std::mutex> mapLocks;

	void Run() {
		while (true) {
			std::cout << i << "Try";

			mapLocks[i].lock();

			std::cout << i << "Awake";
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			mapLocks[i].unlock();
		}
	}
};


class B {
	static std::mutex Lock;
	int i = 0;

public:
	B(int i) { this->i = i; }

	void Run() {
		A::mapLocks[0].lock();
			std::cout << i << "\nDONNEEEEEEEEEEEEEEEEEEEEEE\n";
			A::mapLocks[0].unlock();
		
	}
};

std::mutex A::Lock;
std::mutex B::Lock;
std::map<int, std::mutex> A::mapLocks;

int main() {
	
	
	A a(0);
	A b(1);
	B c(1);
	std::thread(&A::Run, &a).detach();
	std::thread(&A::Run, &b).detach();
	std::thread(&B::Run, &c).detach();
	

	while (true);
	return 0;
}*/



int main() {
	BaseRunner r;
	r.Start();
	return 0;
}