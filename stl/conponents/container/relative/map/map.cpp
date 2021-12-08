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
	//vector<double>money{ 100,50,200.1 };
	//vector<string>name{ "zhangsan","lisi","wangwu" };
	//vector<int> age{ 20,30,40 };
	//map< holder,int,compare_with_money>holders;
	////map< holder, int, compare_with_money_struct>holders;
	//int n = money.size();
	//vector<holder>h(n);
	//for (int i = 0; i < n; ++i) {
	//	h[i].money = money[i];
	//	h[i].name = name[i];
	//	h[i].age = age[i];
	//	holders.insert(make_pair(h[i],i));
	//}
	//map < holder, int, compare_with_money_struct>::iterator it = holders.begin();
	//while (it != holders.end()) {
	//	cout <<"money:" <<it->first.money <<"name:"<< it->first.name<<"age:" << it->first.older << endl;
	//	++it;
	//}
	
	vector<double>money{ 100,50,200.1 };
	vector<string>name{ "zhangsan","lisi","wangwu" };
	vector<int> age{ 20,30,40 };
	int n = money.size();
	//class 内
	map<people, int>persons;
	for (int i = 0; i < n; ++i) {
		persons.insert(make_pair(people(name[i], age[i], money[i]), i));
	}
	for (auto it = persons.begin(); it != persons.end(); ++it) {
		cout << "money:" << it->first.h.name << "name:" << it->first.h.name << "age:" << it->first.h.age << endl;
	}
	return 0;


}
