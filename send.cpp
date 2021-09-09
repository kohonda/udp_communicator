#include <thread>
#include <chrono>
#include <iostream>
#include "udp_lib_switcher.hpp"
#include "msg_A.hpp"

int main()
{
	udp_lib::Sender<msg_A> sender("127.0.0.1", 60000);

	msg_A msg;

	const int sleep_time = 1000; // [msec]

	std::cout << "Send every " << sleep_time / 1000.0 << " seconds" << std::endl;

	while (1)
	{
		std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
		msg.time = std::chrono::system_clock::to_time_t(p);
		msg.vec.resize(5);
		msg.type = "test";

		sender.udp_send(msg);

		std::cout << "send :" << std::endl;
		std::cout << "time :" << msg.time << std::endl;
		std::cout << "type : " << msg.type << std::endl;
		std::cout << "vec size : " << msg.vec.size() << std::endl;

		std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
	}

	return 0;
}