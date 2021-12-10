#include"producer.h"
#include"consumer.h"
queue<Item> buf;//缓冲区
volatile int Item_ID = 1;//产品ID
mutex Item_mutex; //对产品互斥
mutex Item_counter_mutex; //计数互斥
condition_variable  is_not_full;
condition_variable  is_not_empty;


int main() {
	producer p;
	consumer s;
	thread pro;//一个生产者
	thread con[5];//5个消费者

	pro = std::thread(&producer::porduce_task,&p);
	for (int i = 0; i < 5; ++i) {
		con[i] = std::thread(&consumer::consume_task, &s);
	}
	pro.join();
	for (int i = 0; i < 5; ++i) {
		con[i].join();
	}
	
	return 0;
}