
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

namespace udp_lib
{
	class Sender
	{
	private:
		SOCKET sock_;
		struct sockaddr_in addr_;

	public:
		/*** @brief Construct a Sender object, normal usage
		*
		* @param destination_address: IP address of receiver
		* @param destination_port: Destination port
		*/
		Sender(const std::string &destination_address, const int destination_port)
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
			addr_.sin_family = AF_INET;
			addr_.sin_port = htons(destination_port);
			addr_.sin_addr.S_un.S_addr = INADDR_ANY;
			InetPton(AF_INET, destination_address.c_str(), &addr_.sin_addr.s_addr);

			// Non blocking setting
			u_long val = 1; // 0: blocking, 1: non-blocking
			ioctlsocket(sock_, FIONBIO, &val);
		}

		/*** @brief Construct a Sender object, Set source port
		*
		* @param destination_address: IP address of receiver
		* @param destination_port: Destination port
		* @param source port
		*/
		Sender(const std::string &destination_address, const int destination_port, const int source_port)
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
			addr_.sin_family = AF_INET;
			addr_.sin_port = htons(destination_port);
			addr_.sin_addr.S_un.S_addr = INADDR_ANY;
			InetPton(AF_INET, destination_address.c_str(), &addr_.sin_addr.s_addr);

			// set source port
			struct sockaddr_in source_addr;
			source_addr.sin_family = AF_INET;
			source_addr.sin_addr.S_un.S_addr = INADDR_ANY;
			source_addr.sin_port = htons(source_port);
			// InetPton(AF_INET, destination_address.c_str(), &source_addr.sin_addr.s_addr);

			// Non blocking setting
			u_long val = 1; // 0: blocking, 1: non-blocking
			ioctlsocket(sock_, FIONBIO, &val);
		}

		~Sender()
		{
			closesocket(sock_);
			WSACleanup();
		}

		template <typename MSG_TYPE>
		void udp_send(const MSG_TYPE &msg) const
		{
			if (sendto(sock_, (char *)&msg, sizeof(msg), 0, (struct sockaddr *)&addr_, sizeof(addr_)) < 0)
			{
				std::cerr << "[Error] UDP send Error." << std::endl;
				exit(1);
			}
		}
	};

	class Receiver
	{
	private:
		SOCKET sock_;
		struct sockaddr_in addr_;

	public:
		/*** @brief Construct a Receiver object, normal usage
		*
		* @param source_address: IP address of sender
		* @param receive_port: Destination port
		*/
		Receiver(const std::string &source_address, const int receive_port)
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
			addr_.sin_family = AF_INET;
			addr_.sin_port = htons(receive_port);
			addr_.sin_addr.S_un.S_addr = INADDR_ANY;
			InetPton(AF_INET, source_address.c_str(), &addr_.sin_addr.s_addr);

			// Non blocking setting
			u_long val = 1; // 0: blocking, 1: non-blocking
			ioctlsocket(sock_, FIONBIO, &val);

			if (bind(sock_, (const struct sockaddr *)&addr_, sizeof(addr_)) < 0)
			{
				std::cerr << "[Error] UDP bind error." << std::endl;
				exit(2);
			}
		}

		~Receiver()
		{
			closesocket(sock_);
			WSACleanup();
		}

		template <typename MSG_TYPE>
		bool udp_receive(MSG_TYPE *msg) const
		{
			bool is_receive_msg = false;
			bool is_the_end_of_queue = false;
			while (!is_the_end_of_queue)
			{
				socklen_t len = sizeof(addr_);
				if (recvfrom(sock_, (char *)msg, sizeof(*msg), 0, (struct sockaddr *)&addr_, &len) < 0)
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
