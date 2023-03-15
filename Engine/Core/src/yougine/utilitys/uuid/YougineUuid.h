#pragma once
#include <stduuid/uuid.h>

namespace utility::youginuuid
{
    class YougineUuid
    {
    private:
        std::shared_ptr<uuids::uuid> uuid;
    public:
        YougineUuid();
        YougineUuid(std::string uuid_string);
        std::string convertstring()const;


        bool operator==(const YougineUuid& rhs)const
        {
            return uuid == rhs.uuid;
        }

    };
    struct Hash
    {
    public:
        inline size_t operator()(const std::string uuid_string)const
        {
            return std::hash<std::string>()(uuid_string);
        }

    };
}
