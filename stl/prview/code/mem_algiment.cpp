#include<iostream>
using namespace std;

struct mem_1 {
	int x;
	char str1;
};

struct mem_2 {
	int x;
	char str1;
	char str2;
};

struct mem_3 {
	char str1;
	int x;
	char str2;
};

struct mem_4 {
	char str1;
	int x;
	char str2;
};
struct mem_5 {
	char str1;
	int x;
	//int x2;
	double datas; //->8
};

int main() {
	//cout << sizeof(char )<<sizeof(int)<<sizeof(long) << sizeof(double) << endl;
	cout << sizeof(mem_1) << endl; // ->8
	cout << sizeof(mem_2) << endl; //->8
	cout << sizeof(mem_3) << endl; //->12
	cout << sizeof(mem_4) << endl; //->12
	cout << sizeof(mem_5) << endl; //->12
	return 0;
}