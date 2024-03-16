#pragma once
#include <any>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "./../utilitys/uuid/YougineUuid.h"
#include "./../components/ComponentExportParameters/ComponentExportParameter.h"
namespace yougine::managers
{


    /*
     * シーンにあるcomponent全てのSerializefieldのリストを使う
     */
    class ComponentExportParameterManager
    {
    private:
        /*
         * \brief uuid（コンポーネントのuuid）とそのコンポーネントのエクスポートしたいパラメータ(ComponentExportParameter)
         */
        std::map<std::shared_ptr<utility::youginuuid::YougineUuid>, std::shared_ptr<components::componentexportparameter::ComponentExportParameter>> serializefield_list;
    public:
        void Add(std::shared_ptr<utility::youginuuid::YougineUuid> uuid, std::shared_ptr<components::componentexportparameter::ComponentExportParameter> serializefield);
        std::shared_ptr<components::componentexportparameter::ComponentExportParameter> GetSerializeField(std::shared_ptr<utility::youginuuid::YougineUuid> uuid);

    };
}
