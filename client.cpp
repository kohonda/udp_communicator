#include <iostream>
#include "udp_lib_switcher.hpp"
#include "msg_A.hpp"

int main()
{

	udp::UDPLib client("127.0.0.1", 4001);

	client.udp_bind();

	msg_A msg;

	while (1)
	{
		client.udp_receive(&msg);

		std::cout << "Receive_type: " << msg.type << std::endl;
		std::cout << "Receive_x: " << msg.x << std::endl;
	}
	return 0;
}