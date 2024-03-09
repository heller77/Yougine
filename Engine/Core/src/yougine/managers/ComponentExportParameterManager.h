#pragma once
#include <any>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "./../utilitys/uuid/YougineUuid.h"

namespace yougine::managers
{
    class ComponentExportParameter
    {
    private:
        std::vector<std::vector<std::any>> accessable_properties_list;
    };

    /*
     * シーンにあるcomponent全てのSerializefieldのリストを使う
     */
    class ComponentExportParameterManager
    {
    private:
        std::map<std::shared_ptr<utility::youginuuid::YougineUuid>, std::shared_ptr<ComponentExportParameter>> serializefield_list;
    public:
        void Add(std::shared_ptr<utility::youginuuid::YougineUuid> uuid, std::shared_ptr<ComponentExportParameter> serializefield);
        std::shared_ptr<ComponentExportParameter> GetSerializeField(std::shared_ptr<utility::youginuuid::YougineUuid> uuid);

    };
}
