#include <iostream>
#include <chrono>
#include <thread>
#include "udp_lib_switcher.hpp"
#include "msg_A.hpp"

int main()
{

	udp_lib::Receiver receiver("127.0.0.1", 60000);

	const int sleep_time = 2000; // [msec]

	std::cout << "Receive every " << sleep_time / 1000.0 << " seconds" << std::endl;

	while (1)
	{
		msg_A msg;

		if (receiver.udp_receive(&msg))
		{
			std::cout << "time : " << msg.time << std::endl;
			std::cout << "Receive_x : " << msg.x << std::endl;
		}
		else
		{
			std::cout << "Not receive new msg yet." << std::endl;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
	}
	return 0;
}