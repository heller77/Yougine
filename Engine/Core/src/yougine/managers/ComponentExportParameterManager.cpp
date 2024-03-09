#include "ComponentExportParameterManager.h"

void yougine::managers::ComponentExportParameterManager::Add(std::shared_ptr<utility::youginuuid::YougineUuid> uuid,
    std::shared_ptr<ComponentExportParameter> serializefield)
{
    this->serializefield_list[uuid] = serializefield;
}

std::shared_ptr<yougine::managers::ComponentExportParameter> yougine::managers::ComponentExportParameterManager::
GetSerializeField(std::shared_ptr<utility::youginuuid::YougineUuid> uuid)
{
    return this->serializefield_list[uuid];
}

