#include <thread>
#include <chrono>
#include <iostream>
#include "udp_lib_switcher.hpp"
#include "msg_A.hpp"

int main()
{
	udp::UDPLib<msg_A> server("127.0.0.1", 5555);

	msg_A msg;

	constexpr int sleep_time = 1000; // [msec]

	msg.x = 0;
	msg.y = 30;
	msg.z = 40;
	msg.type = 3;

	while (1)
	{

		std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
		msg.time = std::chrono::system_clock::to_time_t(p);

		server.udp_send(msg);

		std::cout << "Send_time : " << msg.time << std::endl;
		std::cout << "Send_type : " << msg.type << std::endl;
		std::cout << "Send_x : " << msg.x << std::endl;

		std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
	}

	return 0;
}