
#ifndef UDP_LIB_WIN
#define UDP_LIB_WIN

#include <winsock2.h>
#include <stdio.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <WinSock2.h>
#include <Windows.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

namespace udp
{
    template <typename MSG_TYPE>
    class UDPLib
    {
    private:
        SOCKET sock_;
        struct sockaddr_in server_addr_;
        struct sockaddr_in client_addr_;

    public:
        UDPLib(const std::string &address, const int port)
        {

            WSADATA wsaData;
            WSAStartup(MAKEWORD(2, 0), &wsaData);
            // Generate socket
            // AF_INET: IPV4, SOCK_DGRAM: UDP, 0: protocol is automoatically chosen
            sock_ = socket(AF_INET, SOCK_DGRAM, 0);
            if (sock_ < 0)
            {
                std::cerr << "[Error] Socket initialize error." << std::endl;
                exit(0);
            }

            // IP/port setting
            server_addr_.sin_family = AF_INET;
            server_addr_.sin_port = htons(port);
            server_addr_.sin_addr.S_un.S_addr = INADDR_ANY;
            InetPton(AF_INET, address.c_str(), &server_addr_.sin_addr.s_addr);

            // Non blocking setting
            u_long val = 1; // 0: blocking, 1: non-blocking
            ioctlsocket(sock_, FIONBIO, &val);
        }

        ~UDPLib()
        {
            closesocket(sock_);
            WSACleanup();
        }

        void udp_bind() const
        {
            if (bind(sock_, (const struct sockaddr *)&server_addr_, sizeof(server_addr_)) < 0)
            {
                std::cerr << "[Error] UDP bind error." << std::endl;
                exit(2);
            }
        }

        void udp_send(const MSG_TYPE &msg) const
        {
            if (sendto(sock_, (char *)&msg, sizeof(msg), 0, (struct sockaddr *)&server_addr_, sizeof(server_addr_)) < 0)
            {
                std::cerr << "[Error] UDP send Error." << std::endl;
                exit(1);
            }
        }

        bool udp_receive(MSG_TYPE *msg) const
        {
            bool is_receive_msg = false;
            bool is_the_end_of_queue = false;
            while (!is_the_end_of_queue)
            {
                socklen_t len = sizeof(client_addr_);
                if (recvfrom(sock_, (char *)msg, sizeof(*msg), 0, (struct sockaddr *)&client_addr_, &len) < 0)
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

#endif
