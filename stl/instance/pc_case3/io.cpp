#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

const char* addr = "C:\\Users\\pipixia\\Desktop\\file.txt";

int main() {
	ofstream outfile(addr, ios::app);
	if (!outfile) {
		std::cout << "can't open the file" << std::endl;
		exit(1);
	}
	vector<string>res;
	res.emplace_back("abc");
	res.emplace_back("abcd");
	res.emplace_back("abce");
	res.emplace_back("abc.031f");
	res.emplace_back("abcg");
	res.emplace_back("abchasd");
	res.emplace_back("abci");
	res.emplace_back("abcjj");
	res.emplace_back("abckkasd");
	res.emplace_back("abasdc");
	
	for (auto& it : res) {
		outfile << it << endl;
	}
	return 0;
}