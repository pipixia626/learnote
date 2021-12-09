#include<future>
#include<thread>
#include<chrono>//for time
#include<iostream>
#include<random>
#include<exception>
using namespace std;

int doSomething(char c) {
	std::default_random_engine dre(c);//种子
	std::uniform_int_distribution<int> id(10, 1000);//随机数范围

	for (int i = 0; i < 10; ++i) {
		this_thread::sleep_for(chrono::microseconds(id(dre)));
		cout.put(c).flush();
	}
	return c;
}

int fun1() {
	return doSomething('.');
}
int fun2() {
	return doSomething('+');
}

int main() {
	std::cout << "starting func1() in background" << "and func2()in later" << std::endl;
	std::future<int>res1(std::async(fun1));

	int res2 = fun2();

	//int res = res1.get() + res2;
	int res = res2 + res1.get();
	std::cout << res << std::endl;
	return 0;
}
