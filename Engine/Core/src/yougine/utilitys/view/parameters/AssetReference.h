#pragma once
#include <string>

#include "ParameterView.h"
namespace utility::view::parameters
{
    class AssetReference : public ParameterView
    {
    private:
        std::string label;
        int select_index;
    public:
        void Draw() override;
        AssetReference(std::string label);
    };
}
