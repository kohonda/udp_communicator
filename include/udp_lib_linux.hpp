#ifndef UDP_LIB_LINUX
#define UDP_LIB_LINUX

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <chrono>

namespace udp
{

    template <typename MSG_TYPE>
    class UDPLib
    {
    private:
        int sock_;
        struct sockaddr_in addr_;

    public:
        /**
    　　  * @brief Construct a new UDPLib object, normal usage
    　　  * 
    　　  * @param address: When publisher, Set destination IP address. When subscriber, Set source IP address.  
    　　  * @param port: When publisher, Set destination port. When subscriber, Set source port.
    　　  */
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
        }

        /**
         * @brief Construct a new UDPLib object, can set source port
         * 
         * @param destination_address: When publisher, Set destination IP address. When subscriber, Set source IP address.  
         * @param destination_port
         * @param source_port 
         */
        UDPLib(const std::string &destination_address, const int destination_port, const int source_port)
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
            addr_.sin_addr.s_addr = inet_addr(destination_address.c_str());
            addr_.sin_port = htons(destination_port);

            // set source port
            struct sockaddr_in source_addr;
            source_addr.sin_family = AF_INET;
            source_addr.sin_addr.s_addr = htonl(INADDR_ANY);
            source_addr.sin_port = htons(source_port);

            // Non blocking setting
            const auto val = 1; // 0: blocking, 1: non-blocking
            ioctl(sock_, FIONBIO, &val);

            // bind source port
            if (bind(sock_, (const struct sockaddr *)&source_addr, sizeof(source_addr)) < 0)
            {
                std::cerr << "[Error] UDP bind error." << std::endl;

                exit(2);
            }
        }

        void udp_bind() const
        {
            if (bind(sock_, (const struct sockaddr *)&addr_, sizeof(addr_)) < 0)
            {
                std::cerr << "[Error] UDP bind error." << std::endl;

                exit(2);
            }
        }

        void udp_send(const MSG_TYPE &msg) const
        {
            if (sendto(sock_, &msg, sizeof(msg), 0, (struct sockaddr *)&addr_, sizeof(addr_)) < 0)
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

#endif