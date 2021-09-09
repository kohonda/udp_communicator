# Simple Non-Blocking UDP Library

A header only C++ non-blocking UDP socket library for Windows/Linux.

Get only latest message when received.

## Example

#### Message definition
```c++
struct msg_A
{
    std::time_t time;
    std::string type;
    std::vector<double> vec;

    template <class Archive>
    void serialize(Archive &archive)
    {
        archive(time, type, vec);
    }
};
```

#### Sender example

```c++
#include <thread>
#include <chrono>
#include <iostream>
#include "udp_lib_switcher.hpp"
#include "msg_A.hpp"

int main()
{
	udp_lib::Sender<msg_A> sender("127.0.0.1", 60000);

	msg_A msg;

	const int sleep_time = 1000; // [msec]

	std::cout << "Send every " << sleep_time / 1000.0 << " seconds" << std::endl;

	while (1)
	{
		std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
		msg.time = std::chrono::system_clock::to_time_t(p);
		msg.vec.resize(5);
		msg.type = "test";

		sender.udp_send(msg);

		std::cout << "send :" << std::endl;
		std::cout << "time :" << msg.time << std::endl;
		std::cout << "type : " << msg.type << std::endl;
		std::cout << "vec size : " << msg.vec.size() << std::endl;

		std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
	}

	return 0;
}
```

#### Receiver exapmple

```c++
#include <iostream>
#include <chrono>
#include <thread>
#include "udp_lib_switcher.hpp"
#include "msg_A.hpp"

int main()
{

	udp_lib::Receiver<msg_A> receiver("127.0.0.1", 60000);

	msg_A msg;

	const int sleep_time = 2000; // [msec]

	std::cout << "Receive every " << sleep_time / 1000.0 << " seconds" << std::endl;

	while (1)
	{

		if (receiver.udp_receive(&msg))
		{
			std::cout << "time : " << msg.time << std::endl;
			std::cout << "type : " << msg.type << std::endl;
			std::cout << "vec_size : " << msg.vec.size() << std::endl;
		}
		else
		{
			std::cout << "Not receive new msg yet." << std::endl;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
	}
	return 0;
}
```

## How to test example

### Linux
#### 1. Build
```bash
cd udp_communicator
mkdir build
cd build
cmake ..
make
```
#### 2. Run
```bash
cd build
./bin/receive
```
On another terminal
```bash
cd build
./bin/send
```

### Windows with MSBuild
#### 1. Build
```bash
cd udp_communicator
mkdir build
cd build
cmake ..
MSBuild.exe .\ALL_BUILD.vcxproj
```

#### 2. Run
```bash
./bin/Release/receive.exe
```
On another terminal
```bash
./bin/Release/send.exe
```

![example](img/example.png)

## TODO
- PC間通信テスト
- cereal,archive関数隠蔽
- 通信プロトコル切り替え
- windows対応
- 通信速度を上げたときの挙動