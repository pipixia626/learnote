#include<atomic>
#include<iostream>
#include<chrono>
#include<thread>
#include<future>
using namespace std;
atomic<bool>readflag(false);
int datas = 0;
void producer() {
	cout << "I am producer" << endl;
	
	datas = 10;
	
	readflag.store(true);
}

void consumer() {
	while (!readflag.load())
	{
		cout << "I am consumer" << endl;
		//this_thread::sleep_for(chrono::microseconds(100));
	}
	cout << "data is :" << datas << endl;
}

int main() {
	auto p = std::async(std::launch::async, producer);
	auto q = std::async(std::launch::async, consumer);
	return 0;
}