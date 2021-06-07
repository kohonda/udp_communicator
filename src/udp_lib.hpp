#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

namespace udp
{
    class UDPLib
    {
    private:
        int sock;
        struct sockaddr_in addr;
        static constexpr int BUFFER_SIZE = 1024;

    public:
        UDPLib(const std::string &address, const int port);
        ~UDPLib();

        void udp_send(const void *msg, const size_t length) const;

        void udp_bind() const;

        void udp_receive(char *buffer) const;
    };
}
