#include <ctime>
// TODO: 以下のインクルードを隠蔽する&serializeも
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <cereal/cereal.hpp>

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