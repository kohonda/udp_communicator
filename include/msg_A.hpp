#include <ctime>
#include <string>

#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>

struct msg_A
{
    std::time_t time;
    std::string type = "";
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;

    template <class Archive>
    void serialize(Archive &archive)
    {
        archive(time, type, x, y, z);
    }
};