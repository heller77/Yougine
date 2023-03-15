#include "YougineUuid.h"

utility::youginuuid::YougineUuid::YougineUuid()
{
    std::random_device rd;
    auto seed_data = std::array<int, std::mt19937::state_size> {};
    std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
    std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
    std::mt19937 generator(seq);
    uuids::uuid_random_generator gen{ generator };
    auto tmp_uuid = gen();
    this->uuid = std::shared_ptr<uuids::uuid>(&tmp_uuid, [](uuids::uuid*) {});

}

utility::youginuuid::YougineUuid::YougineUuid(std::string uuid_string)
{
    auto id = uuids::uuid::from_string(uuid_string).value();
    this->uuid = std::shared_ptr<uuids::uuid>(&id, [](uuids::uuid*) {});
}

std::string utility::youginuuid::YougineUuid::convertstring()const
{
    return to_string(*this->uuid.get());
}
