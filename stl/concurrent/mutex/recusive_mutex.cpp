#include<mutex>
#include<thread>
#include<iostream>

class DataBaseAccess {
private:
	std::recursive_mutex dbMutex;
	 int data = 10;
public:
	void addData() {
		std::lock_guard<std::recursive_mutex>lg(dbMutex);
		
		std::cout << "in adddata(),before data is:" << data << std::endl;
		data += 10;
		std::cout << "in adddata(),after data is:" << data << std::endl;

	}

	void mutipleData() {
		std::lock_guard<std::recursive_mutex>lg(dbMutex);

		std::cout << "in mutipledata(),before data is:" << data << std::endl;
		data *= 10;
		std::cout << "in mutipledata(),after data is:" << data << std::endl;
	}

	void add_mutiplData() {
		std::lock_guard<std::recursive_mutex>lg(dbMutex);
		data += 10;
		mutipleData();
	}
};

int main() {
	DataBaseAccess base;
	std::thread t1(&DataBaseAccess::addData, &base);
	std::thread t2(&DataBaseAccess::mutipleData, &base);

	t1.join();
	t2.join();
	return 0;
}