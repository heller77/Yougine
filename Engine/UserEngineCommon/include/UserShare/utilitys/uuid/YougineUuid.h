#pragma once
#include <stduuid/uuid.h>

#include "UserShare/MacroDifHeader.h"

namespace utility::youginuuid
{
    class EXPORT YougineUuid
    {
    private:
        std::shared_ptr<uuids::uuid> uuid;
        // uuids::uuid* uuid_default_ptr;
        // std::string uuid_text;
    public:
        YougineUuid();
        YougineUuid(std::string uuid_string);
        std::string convertstring()const;
        // std::string GetUUidfromptr();



        bool operator==(const YougineUuid& rhs)const
        {
            return uuid == rhs.uuid;
        }

    };
    struct Hash
    {
    public:
        inline size_t operator()(const YougineUuid uuid_string)const
        {
            return std::hash<std::string>()(uuid_string.convertstring());
        }

    };
}
