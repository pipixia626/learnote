#include<future>
#include<thread>
#include<iostream>
#include<exception>
#include<stdexcept>
using namespace std;

int input_num() {
	cout << "read number:" ;
	int num;
	cin >> num;

	if (!cin) {
		throw runtime_error("no number read");
	}
	return num;
}

void doSomething(char c, shared_future<int>f) {
	try {
		int num = f.get();

		for (int i = 0; i < num; ++i) {
			this_thread::sleep_for(chrono::microseconds(100));
			cout.put(c).flush();
		}
	}
	catch (const exception& e) {
		cerr << "exception in thread" << this_thread::get_id() << ":" << e.what() << endl;

	}
}

int main() {
	try {
		shared_future<int>f = async(input_num);
		auto f1 = async(launch::async, doSomething, '.', f);
		auto f2 = async(launch::async, doSomething, '+', f);
		auto f3 = async(launch::async, doSomething, '*', f);

		f1.get();
		f2.get();
		f3.get();

	}
	catch (const exception& e) {
		cerr << "exception in " << e.what() << endl;
	}
	cout << "done" << endl;
	return 0;
}