#include "udp_lib.hpp"
#include "msg_A.hpp"

int main()
{

    udp::UDPLib client("0.0.0.0", 4001);

    client.udp_bind();

    msg_A msg;
    char txt[100];

    while (1)
    {
        client.udp_receive(&msg);
        // client.udp_receive(&txt);

        std::cout << msg.type << std::endl;
        // std::cout << txt << std::endl;
    }
    return 0;
}