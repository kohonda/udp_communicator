#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <memory>

namespace udp
{
    class UDPLib
    {
    private:
        int sock_;
        struct sockaddr_in addr_;

    public:
        UDPLib(const std::string &address, const int port);
        ~UDPLib();

        void udp_bind() const;

        template <typename MSG>
        void udp_send(const MSG *msg) const
        {
            if (sendto(sock_, (void *)msg, sizeof(msg), 0, (struct sockaddr *)&addr_, sizeof(addr_)) < 0)
            {
                std::cerr << "[Error] UDP send Error." << std::endl;
                exit(1);
            }
        }

        template <typename MSG>
        void udp_receive(MSG *msg) const
        {
            if (recv(sock_, (void *)msg, sizeof(msg), 0) < 0)
            {
                std::cerr << "[Error] UDP received data size is invalid." << std::endl;
                exit(2);
            }
        }
    };
}
