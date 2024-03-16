#include "ComponentExportParameterManager.h"

void yougine::managers::ComponentExportParameterManager::Add(std::shared_ptr<utility::youginuuid::YougineUuid> uuid,
    std::shared_ptr<components::componentexportparameter::ComponentExportParameter> serializefield)
{
    this->serializefield_list[uuid] = serializefield;
}

std::shared_ptr<yougine::components::componentexportparameter::ComponentExportParameter> yougine::managers::ComponentExportParameterManager::
GetSerializeField(std::shared_ptr<utility::youginuuid::YougineUuid> uuid)
{
    return this->serializefield_list[uuid];
}

