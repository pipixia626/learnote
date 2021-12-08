#include<iostream>
#include<string>
#include<vector>
#include<memory>
using namespace std;

int main() {
	shared_ptr<string>BeiJingBank(new string("techo"),
		[](string* p) {
		cout << "delete" << *p << endl;
		delete p;
		});
	//shared_ptr<string>BeiJingBank {new string("ke")};
	//shared_ptr<string>BeiJingBank = make_shared<string>("ke");
	shared_ptr<string>ShenZhenBank(new string("produce"));
	shared_ptr<string>ShangHaiBank(new string("echom"));

	vector<shared_ptr<string>>place;
	place.emplace_back(BeiJingBank);
	place.emplace_back(ShenZhenBank);
	place.emplace_back(BeiJingBank);
	place.emplace_back(ShenZhenBank);
	place.emplace_back(ShangHaiBank);

	for (auto ptr : place) {

		cout << *ptr << " ";
	}
	cout << endl;

	*BeiJingBank = "kechuang";
	for (auto ptr : place) {
		cout << *ptr << " ";
	}
	return 0;
}