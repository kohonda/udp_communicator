# udp_communicator

Linux/Windows対応
header only udp通信ライブラリとサンプルコード

## How to use
1. `include`フォルダに入っている
- udp_lib_linux.hpp
- udp_lib_windows.hpp
- udp_lib_switcher.hpp
をincludeする

2. 通信するデータを構造体で定義して使う

## How to test sample code

### Linux/WSL2
#### 1. Build
```
cd udp_communicator
mkdir build
cd build
cmake ..
make
```
#### Run
```
cd build
./bin/client
```
別のターミナルにて
```
cd build
./bin/server
```

### Windows
#### 1. Build
powershellまたは，コマンドプロンプトにて
```
cd udp_communicator
mkdir build
cd build
cmake ..
MSBuild.exe .\ALL_BUILD.vcxproj
```

#### 2. Run
powershellまたは，コマンドプロンプトにて
```
./bin/Release/client.exe
```
別のpowershellまたは，コマンドプロンプトにて
```
./bin/Release/server.exe
```