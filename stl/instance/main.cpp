#include"producer.h"
#include"consumer.h"
queue<Item> buf;//������
volatile int Item_ID = 1;//��ƷID
mutex Item_mutex; //�Բ�Ʒ����
mutex Item_counter_mutex; //��������
condition_variable  is_not_full;
condition_variable  is_not_empty;


int main() {
	producer p;
	consumer s;
	thread pro;//һ��������
	thread con[5];//5��������

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