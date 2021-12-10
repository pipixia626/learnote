#include"consumer.h"
extern queue<Item> buf;
extern volatile int Item_ID;
extern mutex Item_mutex;
extern mutex Item_counter_mutex;
extern condition_variable  is_not_full;
extern condition_variable  is_not_empty;


void consumer::consume_task()
{
	bool ready_to_exit = false;
	static int count = 1;
	while (1) {
		std::this_thread::sleep_for(chrono::microseconds(100));
		//对产品计数的互斥访问
		std::unique_lock<std::mutex>counter_lock(Item_counter_mutex);

		if (count<=num_of_product) {
			cout << "consumer is consume the th" << count << "product" << endl;
			consume();
		}
		else {
		ready_to_exit = true;
        }
		//消费完缓冲区的所有产品
		if (ready_to_exit)break;
	}
}

void consumer::consume()
{
	std::unique_lock<std::mutex>item_lock(Item_mutex);
	while (buf.empty())
	{
		cout << "consumer is waiting to get item .... " << endl;
		is_not_empty.wait(item_lock);
	}

	//获得产品
	Item item = buf.front();
	buf.pop();

	cout << "Thread ID: " << this_thread::get_id() << " consume Item ID:  " << item.ID << " value is " << item.value << endl;
	//消费产品
	item.value %= 100;//模100
	cout << "after consume the value is ::  " << item.value << endl;

	is_not_full.notify_all();
	item_lock.unlock();
}

void consumer::test_get_data()
{
}
