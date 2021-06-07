#include <unistd.h>

#include "udp_lib.hpp"
#include "msg_A.hpp"

int main()
{
    udp::UDPLib server("0.0.0.0", 4001);

    msg_A msg;
    const std::unique_ptr<msg_A> msg_ptr = std::make_unique<msg_A>(msg);

    while (1)
    {
        server.udp_send(&msg_ptr);
        usleep(1000000);
    }

    return 0;
}