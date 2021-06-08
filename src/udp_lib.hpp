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
        UDPLib(const std::string &address, const int port)
        {
            // Generate socket
            // AF_INET: IPV4, SOCK_DGRAM: UDP, 0: protocol is automoatically chosen
            sock_ = socket(AF_INET, SOCK_DGRAM, 0);
            if (sock_ < 0)
            {
                std::cerr << "[Error] Socket initialize error." << std::endl;
                exit(0);
            }

            // IP/port setting
            addr_.sin_family = AF_INET;
            addr_.sin_addr.s_addr = inet_addr(address.c_str());
            addr_.sin_port = htons(port);
        }

        ~UDPLib()
        {
            close(sock_);
        }

        void udp_bind() const
        {
            if (bind(sock_, (const struct sockaddr *)&addr_, sizeof(addr_)) < 0)
            {
                std::cerr << "[Error] UDP bind error." << std::endl;
                exit(2);
            }
        }

        template <typename MSG>
        void udp_send(const MSG *msg) const
        {
            char *send_data = nullptr;
            send_data = (char *)msg;
            // if (sendto(sock_, (char *)msg, sizeof(msg), 0, (struct sockaddr *)&addr_, sizeof(addr_)) < 0)
            if (sendto(sock_, send_data, sizeof(send_data), 0, (struct sockaddr *)&addr_, sizeof(addr_)) < 0)
            {
                std::cerr << "[Error] UDP send Error." << std::endl;
                exit(1);
            }
        }

        template <typename MSG>
        void udp_receive(MSG *msg) const
        {
            char *received_data;
            memset(received_data, 0, sizeof(msg));
            socklen_t len = sizeof(addr_);
            // if (recvfrom(sock_, (char *)msg, sizeof(msg), 0, (struct sockaddr *)&addr_, &len) < 0)
            if (recvfrom(sock_, received_data, sizeof(received_data), 0, (struct sockaddr *)&addr_, &len) < 0)
            {
                std::cerr << "[Error] UDP received data size is invalid." << std::endl;
                exit(2);
            }
            // TODO : Need convert byte to MSG
            msg = (MSG *)received_data;
        }
    };
}
