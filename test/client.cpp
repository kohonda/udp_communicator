#include "udp_lib.hpp"

int main()
{

    udp::UDPLib client("0.0.0.0", 4001);

    client.udp_bind();

    char msg[100];

    while (1)
    {
        client.udp_receive(msg);
        std::cout << std::string(msg) << std::endl;
    }
    return 0;
}