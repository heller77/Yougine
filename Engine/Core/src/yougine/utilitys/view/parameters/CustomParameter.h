#pragma once
#include <functional>

#include "ParameterView.h"

namespace utility::view::parameters
{
    class CustomParameter :public ParameterView
    {
    private:
        std::function<void()> draw_func;
    public:
        CustomParameter(std::function<void()> draw_func);
        void Draw() override;
        void SetDrawFunc(std::function<void()> draw_func);
    };
}
