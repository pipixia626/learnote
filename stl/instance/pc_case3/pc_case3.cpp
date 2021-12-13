#include<iostream>
#include<mutex>
#include<atomic>
#include<condition_variable>
#include<chrono>
#include<random>
#include<queue>
using namespace std;
const int buf_size = 8;//缓冲区大小
static int born=1;//种子
atomic<bool>finish{ false };
struct Item {
	queue<int>buf;
	mutex item_mutex; //对产品互斥
	mutex item_read;  //多个消费者互斥访问
	atomic<int>write_item_counter{ 0 };//生产者生产计数
	atomic<int>read_item_counter{ 0 };//消费者消费计数
	atomic<int>produce_finish{ false };//生产者生产完成
	atomic<int>consume_finish{ false };//消费者消费完成
	condition_variable is_full;
	condition_variable is_empty;
	const int total = 20;//总任务数
};
Item items;
int get_random_data()
{
	std::default_random_engine dre(born + 'a');//种子
	std::uniform_int_distribution<int> value_s(10, 1000);//随机数范围
	born++;
	return value_s(dre);
}
void produce(Item &item) {
	std::unique_lock<std::mutex>Item_lock(item.item_mutex);
	
	if (item.buf.size() <buf_size) {
		int num = get_random_data();

		item.buf.push(num);

		//item.is_empty.notify_all();
		Item_lock.unlock();//解锁


		cout << "thread id" << this_thread::get_id() << "生产第" << items.write_item_counter.load() + 1 << "个数据：" << num << endl;
		item.write_item_counter++;//原子计数
	}
}

void consume(Item& item) {
	std::unique_lock<std::mutex>Item_lock(item.item_mutex);

	int num = 0;
	if (!item.buf.empty()) {
		num = item.buf.front();
		item.buf.pop();

		//item.is_full.notify_all();
		Item_lock.unlock();

		num %= 100;
		cout << "thread id" << this_thread::get_id() << "消费第" << items.read_item_counter.load() + 1 << "个数据" << " 处理之后是:" << num << endl;

		item.read_item_counter++;//原子计数
	}
}

void produce_task() {
	while (!items.produce_finish.load()) {
		//this_thread::sleep_for(chrono::microseconds(100));
		
		produce(items);
		
		if (items.write_item_counter >= items.total) {
			items.produce_finish.store(true);
		}
		if (items.produce_finish == true)break;
	}
}

void consumer_task() {
	while (!items.consume_finish.load()) {
		this_thread::sleep_for(chrono::microseconds(10));
		std::unique_lock<std::mutex>read_lock(items.item_read);
		consume(items);
		read_lock.unlock();
		if (items.read_item_counter >= items.total) {
			items.consume_finish.store(true);
		}
		if (items.consume_finish == true)break;
	}
}

int main() {
	std::thread produce = std::thread(produce_task);
	std::thread consume[5];
	for (int i = 0; i < 5; ++i) {
		consume[i] = std::thread(consumer_task);
	}
	while (!finish.load()) {
		std::cout << "主线程在等子线程处理任务" << std::endl;
		this_thread::sleep_for(chrono::seconds(5));
		
		if (items.produce_finish.load()) {
			std::cout << "生产者子线程退出" << std::endl;
			produce.join();
		}
		if (items.consume_finish.load()) {
			for (int i = 0; i < 5; ++i) {
				std::cout << "消费者第" << i + 1 << "个子线程退出" << std::endl;
				consume[i].join();
			}
		}
		if (items.produce_finish.load() && items.consume_finish.load()) {
			finish.store(true);
		}
	}
	return 0;
}