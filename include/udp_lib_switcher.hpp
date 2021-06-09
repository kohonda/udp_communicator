
#pragma once

#if defined(_MSC_VER)
#include "udp_lib_windows.hpp"
#elif defined(__linux__)
#include "udp_lib_linux.hpp"
#endif