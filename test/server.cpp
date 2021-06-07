#include <unistd.h>

#include "udp_lib.hpp"
#include "msg_A.hpp"

int main()
{
    udp::UDPLib server("0.0.0.0", 4001);

    const msg_A msg;

    while (1)
    {
        server.udp_send(&msg, sizeof(msg_A));
        usleep(1000000);
    }

    return 0;
}