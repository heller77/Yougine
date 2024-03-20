#include "ComponentExportParameter.h"

int yougine::components::componentexportparameter::ComponentExportParameter::GetSize() const
{
    return this->accessable_properties_list.size();
}

std::any yougine::components::componentexportparameter::ComponentExportParameter::Get(int index)
{
    return this->accessable_properties_list[index];
}
