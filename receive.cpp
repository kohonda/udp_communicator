#include <iostream>
#include <thread>
#include <chrono>
#include "udp_lib_switcher.hpp"
#include "msg_A.hpp"

int main()
{

	udp::UDPLib client("127.0.0.1", 5555);

	client.udp_bind();

	msg_A msg;

	constexpr int sleep_time = 2000; // [msec]

	while (1)
	{
		if (client.udp_receive(&msg))
		{
			std::cout << "Receive_type: " << msg.type << std::endl;
			std::cout << "Receive_x: " << msg.x << std::endl;
		}
		else
		{
			std::cout << "Receive_type: " << msg.type << std::endl;
			std::cout << "Receive_x: " << msg.x << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
		}
	}
	return 0;
}