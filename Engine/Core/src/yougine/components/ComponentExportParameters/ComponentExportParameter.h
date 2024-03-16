#pragma once
#include <vector>
#include <any>
namespace yougine::components::componentexportparameter
{
    class ComponentExportParameter
    {
    private:
        std::vector<std::vector<std::any>> accessable_properties_list;
    };
}
