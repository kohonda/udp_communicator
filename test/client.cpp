#include "udp_lib.hpp"
#include "msg_A.hpp"

int main()
{

    udp::UDPLib client("0.0.0.0", 4001);

    client.udp_bind();

    msg_A msg;
    const std::unique_ptr<msg_A> msg_ptr = std::make_unique<msg_A>(msg);

    while (1)
    {
        client.udp_receive(&msg_ptr);
        std::cout << msg.type << std::endl;
    }
    return 0;
}