#include <unistd.h>

#include "udp_lib.hpp"

int main()
{
    udp::UDPLib server("0.0.0.0", 4001);

    const std::string text = "hello";

    while (1)
    {
        server.udp_send(text.c_str(), sizeof(text.c_str()));
        usleep(1000000);
    }

    return 0;
}