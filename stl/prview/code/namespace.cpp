#include<iostream>
#include<string>
namespace TCP {

	int time;
	std::string content="TCP sended";
	int ack=1;
	int get_SendTime() {
		time = rand() % 60;
		return time;
	}
	bool send() {
		std::cout << "I am TCP" << std::endl;
		std::cout << "send time :" << get_SendTime() << "  Ack: " << ack <<content <<std::endl;
		return true;
	}
}

namespace UDP {
	int time;
	std::string content = "UDP sended";
	int ack = 1;
	int get_SendTime() {
		time = rand() % 60;
		return time;
	}
	bool send() {
		std::cout << "I am UDP" << std::endl;
		std::cout << "send time :" << get_SendTime() << "  Ack: " << ack << content << std::endl;
		return true;
	}
}

int main() {
	TCP::send();
	UDP::send();
	return 0;
}

