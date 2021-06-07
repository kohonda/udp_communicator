add_executable(server server.cpp)

# target_compile_options(udp_lib PUBLIC -O3 -Wall -march=native)
target_compile_options(server PUBLIC -g -Wall)

target_include_directories(
  server
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )

target_link_libraries(
    server
    udp_lib
)


add_executable(client client.cpp)

# target_compile_options(udp_lib PUBLIC -O3 -Wall -march=native)
target_compile_options(client PUBLIC -g -Wall)

target_include_directories(
  client
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )

target_link_libraries(
    client
    udp_lib
)
