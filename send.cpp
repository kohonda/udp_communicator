#include <thread>
#include <chrono>
#include <iostream>
#include "udp_lib_switcher.hpp"
#include "msg_A.hpp"

int main()
{
	udp::UDPLib<msg_A> server("127.0.0.1", 60000);

	msg_A msg;

	const int sleep_time = 1000; // [msec]

	msg.x = 0;

	std::cout << "Send every " << sleep_time / 1000.0 << " seconds" << std::endl;

	while (1)
	{
		std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
		msg.time = std::chrono::system_clock::to_time_t(p);

		msg.x += 1.0;

		// std::stringstream ss;
		// {
		// 	cereal::JSONOutputArchive o_archive(ss);
		// 	o_archive(msg);
		// }

		server.udp_send(msg);

		std::cout << "send :" << std::endl;
		std::cout << msg.time << std::endl;

		std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
	}

	return 0;
}