#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
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

        std::string addres_;
        int port_;

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

            // Non blocking setting
            const auto val = 1; // 0: blocking, 1: non-blocking
            ioctl(sock_, FIONBIO, &val);

            addres_ = address;
            port_ = port;
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
        void udp_send(const MSG &msg) const
        {
            if (sendto(sock_, &msg, sizeof(msg), 0, (struct sockaddr *)&addr_, sizeof(addr_)) < 0)
            {
                std::cerr << "[Error] UDP send Error." << std::endl;
                exit(1);
            }
        }

        template <typename MSG>
        bool udp_receive(MSG *msg)
        {
            bool is_receive_msg = false;
            bool is_the_end_of_queue = false;
            while (!is_the_end_of_queue)
            {
                socklen_t len = sizeof(addr_);
                if (recvfrom(sock_, msg, sizeof(*msg), 0, (struct sockaddr *)&addr_, &len) < 0)
                {
                    is_the_end_of_queue = true;
                }
                else
                {
                    // Keep reading the socket queue until the end.
                    is_the_end_of_queue = false;
                    is_receive_msg = true;
                }
            }

            if (is_receive_msg)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    };
}
