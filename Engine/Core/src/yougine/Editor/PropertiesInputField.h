#pragma once
#include <memory>
#include <string>
#include "../utilitys/YougineMath.h"
#include "../utilitys/Split.cpp"
#include "../utilitys/Quaternion.h"
#include <any>
#include "imgui/imgui.h"

namespace editor
{
    class PropertiesInputField
    {
    public:
        void Draw(std::any val, const char*);

    private:
        void Bool3View(utility::Bool3* value, const char* name);
        void Vector3View(utility::Vector3* value, const char* name);
        void IntView(int* value, const char* name);
        void FloatView(float* value, const char* name);
        void StringView(std::string* value, const char* name);
        void BoolView(bool* value, const char* name);
        void QuaternionView(std::shared_ptr<utility::Quaternion> value, const char* name);
    };
}
