#include "udp_lib.hpp"

namespace udp
{
    UDPLib::UDPLib(const std::string &address, const int port)
    {
        // Generate socket
        // AF_INET: IPV4, SOCK_DGRAM: UDP, 0: protocol is automoatically chosen
        sock = socket(AF_INET, SOCK_DGRAM, 0);
        if (sock < 0)
        {
            std::cerr << "[Error] Socket initialize error." << std::endl;
            exit(0);
        }

        // IP/port setting
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(address.c_str());
        addr.sin_port = htons(port);
    }

    UDPLib::~UDPLib()
    {
        close(sock);
    }

    void UDPLib::udp_send(const void *msg, const size_t length) const
    {
        if (sendto(sock, msg, length, 0, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        {
            std::cerr << "[Error] UDP send Error." << std::endl;
            exit(1);
        }
    }

    void UDPLib::udp_bind() const
    {
        if (bind(sock, (const struct sockaddr *)&addr, sizeof(addr)) < 0)
        {
            std::cerr << "[Error] UDP bind error." << std::endl;
            exit(2);
        }
    }

    void UDPLib::udp_receive(char *buffer) const
    {
        // Initialize Buffer
        memset(buffer, 0, BUFFER_SIZE);
        if (recv(sock, buffer, sizeof(buffer), 0) < 0)
        {
            std::cerr << "[Error] UDP received data size is invalid." << std::endl;
            exit(2);
        }
    }
}