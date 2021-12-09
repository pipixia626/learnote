#include<mutex>
#include<thread>
#include<chrono>
#include<iostream>
#include<string>

using namespace std;

class bank_count{
public:
	bank_count(string name, int money) {
		this->name = name;
		this->money = money;
	}
	void add_money(int amount) {
		money += amount;
	}
	void delete_money(int amount) {
		money -= amount;
	}
	void get_money() {
		cout << "money" <<money<< "   ID:  " << std::this_thread::get_id()<< endl;
	}
	mutex money_mutex;
private:
	string name;
	int money;
};

//转账
void transfer(bank_count& from, bank_count& to, int amount) {
	unique_lock<mutex>lock1(from.money_mutex, defer_lock);
	unique_lock<mutex>lock2(to.money_mutex, defer_lock);
	lock(lock1, lock2);
	from.delete_money(amount);
	to.add_money(amount);
	cout << "I am from ,I have :" << endl;
	from.get_money() ;
	cout << "I am to ,I have :" << endl;
	to.get_money();

}

int main() {
	bank_count b1("user1", 100);
	bank_count b2("user2", 50);

	std::thread t1 (transfer,std::ref(b1),std::ref(b2),10);
	std::thread t2 (transfer, std::ref(b2), std::ref(b1), 20);

	std::cout << "I am the first trans " << std::endl;
	t1.join();
	std::cout << "I am the second trans " << std::endl;
	t2.join();

	return 0;
}