#ifndef UDP_LIB_LINUX
#define UDP_LIB_LINUX

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <cereal/archives/json.hpp>

namespace udp_lib
{
    template <typename MSG_TYPE>
    class Sender
    {
    private:
        int sock_;
        struct sockaddr_in addr_;

    public:
        /**
    　　  * @brief Construct a Sender object, normal usage
    　　  * 
    　　  * @param destination_address: IP address of receiver
    　　  * @param destination_port: Destination port
    　　  */
        Sender(const std::string &destination_address, const int destination_port)
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

            // Non blocking setting
            const auto val = 1; // 0: blocking, 1: non-blocking
            ioctl(sock_, FIONBIO, &val);
        }

        /**
         * @brief Construct a new UDPLib object, Set source port
         * 
         * @param destination_address: IP address of receiver
         * @param destination_port
         * @param source_port 
         */
        Sender(const std::string &destination_address, const int destination_port, const int source_port)
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

        /**
         * @brief Send message by udp
         * 
         * @param [in] sending message 
         */
        void udp_send(const MSG_TYPE &msg) const
        {
            // Serialization
            std::stringstream ss;
            {
                cereal::JSONOutputArchive o_archive(ss);
                o_archive(msg);
            }

            // Send
            if (sendto(sock_, ss.str().c_str(), ss.str().length(), 0, (struct sockaddr *)&addr_, sizeof(addr_)) < 0)
            {
                std::cerr << "[Error] UDP send Error." << std::endl;
                exit(1);
            }
        }
    };

    template <typename MSG_TYPE>
    class Receiver
    {
    private:
        int sock_;
        struct sockaddr_in addr_;
        const int max_msg_byte_size_; // Maximum message buffer size when receiving

    public:
        /**
         * @brief Construct a new Receiver object, normal usage
         * 
         * @param source_address : IP address of the sender
         * @param receive_port 
         * @param max_msg_byte_size : Maximum message buffer size when receiving
         */
        Receiver(const std::string &source_address, const int receive_port, const int max_msg_byte_size = 512) : max_msg_byte_size_{max_msg_byte_size}
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
            addr_.sin_addr.s_addr = inet_addr(source_address.c_str());
            addr_.sin_port = htons(receive_port);

            // Non blocking setting
            const auto val = 1; // 0: blocking, 1: non-blocking
            ioctl(sock_, FIONBIO, &val);

            // bind receive port
            if (bind(sock_, (const struct sockaddr *)&addr_, sizeof(addr_)) < 0)
            {
                std::cerr << "[Error] UDP bind error." << std::endl;

                exit(2);
            }
        }

        /**
         * @brief Construct a new UDPLib object, can receive from any ip-address 
         * 
         * @param receive_port 
         * @param max_msg_byte_size : Maximum message buffer size when receiving
         */
        Receiver(const int receive_port, const int max_msg_byte_size = 512) : max_msg_byte_size_{max_msg_byte_size}
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
            addr_.sin_addr.s_addr = INADDR_ANY;
            addr_.sin_port = htons(receive_port);

            // Non blocking setting
            const auto val = 1; // 0: blocking, 1: non-blocking
            ioctl(sock_, FIONBIO, &val);

            // bind receive port
            if (bind(sock_, (const struct sockaddr *)&addr_, sizeof(addr_)) < 0)
            {
                std::cerr << "[Error] UDP bind error." << std::endl;

                exit(2);
            }
        }

        /**
         * @brief Receive message
         * 
         * @param [in] msg 
         * @return true : Receive message
         * @return false : Not receive message
         */
        bool udp_receive(MSG_TYPE *msg) const
        {
            bool is_receive_msg = false;
            bool is_the_end_of_queue = false;
            char buf[max_msg_byte_size_];
            std::string tmp_msg;

            while (!is_the_end_of_queue)
            {
                socklen_t len = sizeof(addr_);
                memset(buf, 0, sizeof(buf));
                const auto msg_size = recvfrom(sock_, buf, sizeof(buf), 0, (struct sockaddr *)&addr_, &len);
                if (msg_size < 0)
                {
                    is_the_end_of_queue = true;
                }
                else if (msg_size >= max_msg_byte_size_)
                {
                    std::cerr << "[Error] Please set a larger max_msg_byte_size_." << std::endl;
                    exit(3);
                }
                else
                {
                    // Keep reading the socket queue until the end.
                    is_the_end_of_queue = false;
                    is_receive_msg = true;
                    tmp_msg = std::string(buf);
                }
            }

            if (is_receive_msg)
            {
                std::stringstream ss;
                ss << tmp_msg;
                cereal::JSONInputArchive in_archive(ss);
                in_archive(*msg);
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