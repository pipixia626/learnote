#include<iostream>
#include<string>
#include<thread>
#include<mutex>
#include<condition_variable>

std::mutex m;
std::condition_variable cv;
std::string data;
bool ready = false;
bool processed = false;

void transfer() {
	std::unique_lock<std::mutex>lk(m);
	cv.wait(lk, [] {return ready; });
	std::cout << "is transfer money" << std::endl;
	data += "1000";

	processed = true;

	std::cout << "trans signal is completed " << std::endl;
	lk.unlock();

	//cv.notify_all();
}

int main() {
	std::thread t(transfer);
	data = "0+";

	{
		std::unique_lock<std::mutex>lk(m);
		ready = true;
		std::cout << "main is ready to trans" << std::endl;
	}
	
	//cv.notify_all();
	{
		std::unique_lock<std::mutex>lk(m);
		cv.wait(lk, [] {return processed; });
	}

	std::cout << "back data is " << data << std::endl;
	t.join();
	return 0;
}
