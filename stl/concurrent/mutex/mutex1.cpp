#include<future>
#include<mutex>
#include<iostream>
#include<string>
#include<thread>
std::mutex addMutex;

volatile int count = 0;

void add() {
	for (int i = 0; i < 100; ++i) {
		if (addMutex.try_lock()) {
			++count;
			addMutex.unlock();
		}
	}
	std::cout << "id:"<<std::this_thread::get_id()<<"count:"<<count << std::endl;
}

int main() {
	std::thread threads[10];
	for (int i = 0; i < 10; ++i) {
		threads[i] = std::thread(add);
	}
	for (auto& th : threads)th.join();

	return 0;
}
