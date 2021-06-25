#include <thread>
#include <chrono>
#include <iostream>
#include "udp_lib_switcher.hpp"
#include "msg_A.hpp"

int main()
{
    udp::UDPLib server("127.0.0.1", 5555);

    msg_A msg;

    constexpr int sleep_time = 1000; // [msec]

    while (1)
    {
        msg.x = 20;
        msg.y = 30;
        msg.z = 40;
        msg.type = 3;
        server.udp_send(msg);

        std::cout << "Send_type : " << msg.type << std::endl;
        std::cout << "Send_x : " << msg.x << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
    }

    return 0;
}