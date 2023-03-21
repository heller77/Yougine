#include "CustomParameter.h"

utility::view::parameters::CustomParameter::CustomParameter(std::function<void()> draw_func)
{
    this->draw_func = draw_func;
}

void utility::view::parameters::CustomParameter::Draw()
{
    if (draw_func)
    {
        draw_func();
    }
}

void utility::view::parameters::CustomParameter::SetDrawFunc(std::function<void()> draw_func)
{
    this->draw_func = draw_func;
}
