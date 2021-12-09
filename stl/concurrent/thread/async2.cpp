#include<future>
#include<list>
#include<iostream>
#include<exception>
using namespace std;

void task1() {
	list<int>v;
	while (1) {
		for (int i = 0; i < 1000000; ++i) {
			v.emplace_back(i);
		}
		cout.put('.').flush();
	}
}
int main() {
	cout << "starting 2tasks" << endl;
	cout << "task1:process endless loop of memory consumption" << endl;
	cout << "task2: wait for return and then for task1" << endl;

	auto f1 = async(task1);
	cin.get();
	//异常终止线程，因为没有被捕获，则这一状态直到get()被调用->传播出去->main
	try {
		f1.get();
	}
	catch (const exception& e) {
		cerr << "exception:" << e.what() << endl;
	}
}