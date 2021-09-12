#include <iostream>
#include <chrono>
#include <thread>
#include "udp_lib_switcher.hpp"
#include "msg_A.hpp"

int main()
{

	udp_lib::Receiver<msg_A, udp_lib::SERIAL_TYPE::BINARY> receiver("127.0.0.1", 60000);

	msg_A msg;

	const int sleep_time = 2000; // [msec]

	std::cout << "Receive every " << sleep_time / 1000.0 << " seconds" << std::endl;

	while (1)
	{

		if (receiver.udp_receive(&msg))
		{
			std::cout << "time : " << msg.time << std::endl;
			std::cout << "type : " << msg.type << std::endl;
			std::cout << "vec_size : " << msg.vec.size() << std::endl;
		}
		else
		{
			std::cout << "Not receive new msg yet." << std::endl;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
	}
	return 0;
}