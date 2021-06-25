#include <ctime>

struct msg_A
{
    std::time_t time;
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    int type = 0;
};