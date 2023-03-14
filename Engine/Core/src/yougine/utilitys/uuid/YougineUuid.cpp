#include "YougineUuid.h"

utility::youginuuid::YougineUuid::YougineUuid()
{
    std::random_device rd;
    auto seed_data = std::array<int, std::mt19937::state_size> {};
    std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
    std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
    std::mt19937 generator(seq);
    uuids::uuid_random_generator gen{ generator };
    this->uuid = gen();
}

std::string utility::youginuuid::YougineUuid::convertstring()const
{
    return to_string(this->uuid);
}
