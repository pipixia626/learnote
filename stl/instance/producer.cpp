#include"producer.h"
extern queue<Item>buf;
extern volatile int Item_ID ;
extern mutex Item_mutex;
extern mutex Item_counter_mutex;
extern condition_variable  is_not_full;
extern condition_variable  is_not_empty;

void producer::porduce_task() {
	for (int i = 0; i < num_of_product; ++i) {
		cout << "produce the  " << i+1 << "th " << "product" << endl;
		produce_Item();
	}
}

void producer::produce_Item()
{   
	std::unique_lock<std::mutex> item_lock(Item_mutex);
	while (buf.size() == bufSize) {
		cout << "the buf is full ,waiting to consume ...." << endl;
		is_not_full.wait(item_lock);//等待产品库不满的情况


	}
	   //生产产品

		Item item;
		item.ID = Item_ID++;

		

		item.value = get_random_data();
		buf.push(item);

		cout << "Thread ID:" << this_thread::get_id() << " Create Item ID: " << item.ID << "  the value is   " << item.value << endl;
		is_not_empty.notify_all();//唤醒消费者去消费

		item_lock.unlock();
}


//随机产生数据
int producer::get_random_data()
{   
	std::default_random_engine dre(Item_ID+'a');//种子
	std::uniform_int_distribution<int> value_s(10, 1000);//随机数范围

	return value_s(dre);
}
//

//test
void producer::test_random_data()
{
	for (int i = 0; i < 100; ++i) {
		std::default_random_engine dre(Item_ID + 'a');//种子
		std::uniform_int_distribution<int> value_s(10, 1000);//随机数范围
	}
}

void producer::test_produce_Item()
{
	cout << "current queue size is " << buf.size() << endl;
}
