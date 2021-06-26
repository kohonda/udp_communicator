
#ifndef UDP_LIB_SWITCHER
#define UDP_LIB_SWITCHER

#if defined(_MSC_VER)
#include "udp_lib_windows.hpp"
#elif defined(__linux__)
#include "udp_lib_linux.hpp"
#endif

#endif