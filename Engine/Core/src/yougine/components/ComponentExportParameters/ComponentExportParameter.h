#pragma once
#include <vector>
#include <any>
namespace yougine::components::componentexportparameter
{
    /**
     * \brief コンポーネントがエクスポートするパラメータを管理
     */
    class ComponentExportParameter
    {
    private:
        std::vector<std::vector<std::any>> accessable_properties_list;
    public:
        int GetSize() const;
        std::any Get(int index);
    };
}
