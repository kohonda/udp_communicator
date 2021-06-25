cmake_minimum_required(VERSION 3.13)

project(udp_communicator LANGUAGES CXX)

# set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# place binaries and libraries according to GNU standards
include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})


add_executable(send send.cpp)
add_executable(receive receive.cpp)
# add_executable(node_1 node_1.cpp)
# add_executable(node_2 node_2.cpp)

target_compile_options(send PUBLIC -O3 -Wall)
# target_compile_options(send PUBLIC -g -Wall)
target_include_directories(
    send
    PUBLIC
    include
)

target_compile_options(receive PUBLIC -O3 -Wall)
# target_compile_options(receive PUBLIC -g -Wall)
target_include_directories(
    receive
    PUBLIC
    include
)

# target_compile_options(node_1 PUBLIC -O3 -Wall)
# # target_compile_options(node_1 PUBLIC -g -Wall)
# target_include_directories(
#     node_1
#     PUBLIC
#     include
# )

# target_compile_options(node_2 PUBLIC -O3 -Wall)
# # target_compile_options(node_2 PUBLIC -g -Wall)
# target_include_directories(
#     node_2
#     PUBLIC
#     include
# )

