#include <unistd.h>

#include "udp_lib.hpp"
#include "msg_A.hpp"

int main()
{
    udp::UDPLib server("0.0.0.0", 4001);

    msg_A msg;
    msg.x = 20;
    msg.y = 30;
    msg.z = 40;
    msg.type = 3;

    char txt[100] = "hello";

    while (1)
    {
        server.udp_send(&msg);
        // server.udp_send(&txt);

        usleep(1000000);
    }

    return 0;
}