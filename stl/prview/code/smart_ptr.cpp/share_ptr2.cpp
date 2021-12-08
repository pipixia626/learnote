#include<iostream>
#include<string>
#include<vector>
#include<memory>
using namespace std;

class Person {
public:
	string name;
	shared_ptr<Person>mother;
	shared_ptr<Person>farther;
	vector<shared_ptr<Person>>kids;

	Person(const string& n,
		shared_ptr<Person>m = nullptr,
		shared_ptr<Person>f = nullptr)
		:name(n), mother(m), farther(f) {

	}
	~Person() {
		cout << "delete" << name << endl;
	}
};

shared_ptr<Person> initFamily(const string& name) {
	shared_ptr<Person>mom(new Person(name + "'s mom"));
	shared_ptr<Person>dad(new Person(name + "'s dad"));
	shared_ptr<Person>kid(new Person(name, mom, dad));

	mom->kids.emplace_back(kid);
	dad->kids.emplace_back(kid);
	return kid;
}

int main() {
	shared_ptr<Person>p = initFamily("zhangsan");

	cout << "init" << endl;
	cout << "shared " << p.use_count() << "times" << endl;
	cout << "1st kid of mom:" << p->mother->kids[0]->name << endl;

	p = initFamily("lisi");
}