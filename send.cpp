#include <thread>
#include <chrono>
#include <iostream>
#include "udp_lib_switcher.hpp"
#include "control_msg.hpp"

int main()
{
	udp::UDPLib<ControlMsg> server("192.168.140.210", 60001);

	ControlMsg msg;

	const int sleep_time = 100; // [msec]

	// msg.x = 0;
	// msg.y = 30;
	// msg.z = 40;
	// msg.type = 3;

	std::cout << "Send every " << sleep_time / 1000.0 << " seconds" << std::endl;

	while (1)
	{

		// std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
		// msg.time = std::chrono::system_clock::to_time_t(p);

		server.udp_send(msg);

		msg.time_counter = 1.0;

		msg.steer_cmd += 1.0;

		// std::cout << "Send_time : " << msg.time << std::endl;
		// std::cout << "Send_type : " << msg.type << std::endl;
		// std::cout << "Send_x : " << msg.x << std::endl;

		std::cout << "send: " << msg.steer_cmd << std::endl;

		std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
	}

	return 0;
}