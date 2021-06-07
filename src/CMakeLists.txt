add_library(udp_lib)

# target_compile_options(udp_lib PUBLIC -O3 -Wall -march=native)
target_compile_options(udp_lib PUBLIC -g -Wall)

target_sources(
    udp_lib
    PRIVATE
    udp_lib.cpp
    PUBLIC
    udp_lib.hpp
)

target_include_directories(udp_lib
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(
    udp_lib
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
