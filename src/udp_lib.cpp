#include "udp_lib.hpp"

namespace udp
{
    UDPLib::UDPLib(const std::string &address, const int port)
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

    UDPLib::~UDPLib()
    {
        close(sock_);
    }

    void UDPLib::udp_bind() const
    {
        if (bind(sock_, (const struct sockaddr *)&addr_, sizeof(addr_)) < 0)
        {
            std::cerr << "[Error] UDP bind error." << std::endl;
            exit(2);
        }
    }
}