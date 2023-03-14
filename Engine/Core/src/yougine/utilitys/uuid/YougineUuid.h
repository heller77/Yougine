#pragma once
#include <stduuid/uuid.h>

namespace utility::youginuuid
{
    class YougineUuid
    {
    private:
        uuids::uuid uuid;
    public:
        YougineUuid();
        std::string convertstring()const;


        bool operator==(const YougineUuid& rhs)const
        {
            return uuid == rhs.uuid;
        }

    };
    struct Hash
    {
    public:
        inline size_t operator()(const std::shared_ptr<YougineUuid> uuid)const
        {
            return std::hash<std::string>()(uuid->convertstring());
        }

    };
}
