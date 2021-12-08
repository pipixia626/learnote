#include<iostream>
#include<map>
#include<set>
#include<vector>
#include<string>
using namespace std;
struct holder {
	double money;
	int age;
	string name;
	holder() :money(0), age(0), name("") {};
	void none(){}
};
//仿函数
class compare_with_money {
public:
	bool operator()(const holder& a,  const holder& b )const {
		if (a.money == b.money)return a.age >= b.age;
		else return a.money > b.money;
	}
};


//直接函数
struct compare_with_money_struct {
	bool operator()( const holder& a, const  holder& b)const {
		if (a.money == b.money)return a.age >= b.age;
		else return a.money > b.money;
	}
};

//类内
class people {
public:
	holder h;
	people(string _name, int _age,double _money) {
		this->h.name = _name;
		this->h.age = _age;
		this->h.money = _money;
	}
	const double get_money()const {
		return this->h.money;
	}
	const string get_name() const{
		return h.name;
	}
	const int get_age() const{
		return h.age;
	}
	//根据钱数大小来比较
	bool operator<(const people& p)const
	{
		return h.money >= p.h.money;
	}

};
//class内
int main() {	
	
	vector<double>money{ 100,50,200.1 };
	vector<string>name{ "zhangsan","lisi","wangwu" };
	vector<int> age{ 20,30,40 };
	int n = money.size();
	//class 内
	set<people>persons;
	for (int i = 0; i < n; ++i) {
		persons.insert(people(name[i], age[i], money[i]));
	}
	for (auto it = persons.begin(); it != persons.end(); ++it) {
		cout << "money:" << it->h.money << "name:" << it->h.name << "age:" << it->h.age << endl;
	}
	return 0;


}
