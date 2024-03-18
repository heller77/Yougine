#include "YougineUuid.h"

utility::youginuuid::YougineUuid::YougineUuid()
{
    std::random_device rd;
    auto seed_data = std::array<int, std::mt19937::state_size> {};
    std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
    std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
    std::mt19937 generator(seq);
    uuids::uuid_random_generator gen{ generator };
    auto id = gen();

    auto uuid = new uuids::uuid(id);//これでコピーできてる？
    this->uuid = std::shared_ptr<uuids::uuid>(uuid);

}

utility::youginuuid::YougineUuid::YougineUuid(std::string uuid_string)
{
    auto id = uuids::uuid::from_string(uuid_string).value();
    auto uuid = new uuids::uuid(id);
    this->uuid = std::shared_ptr<uuids::uuid>(uuid);
    // this->uuid = std::shared_ptr<uuids::uuid>(&id, [](uuids::uuid*) {});
    // this->uuid_text = uuid_string;
}

std::string utility::youginuuid::YougineUuid::convertstring()const
{
    return to_string(*this->uuid);
    // return this->uuid_text;
}

// std::string utility::youginuuid::YougineUuid::GetUUidfromptr()
// {
//     return to_string(*this->uuid);
// }
