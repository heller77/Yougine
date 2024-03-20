#pragma once
#include <memory>
#include <string>
#include "UserShare/utilitys/YougineMath.h"
#include "UserShare/utilitys/Split.h"
#include "UserShare/utilitys/Quaternion.h"
#include <any>
#include "imgui/imgui.h"

namespace editor
{
    class PropertiesInputField
    {
    public:
        /**
         * \brief
         * @fn
         *
         * InputFieldを描画する
         * valの真の型を判別しInputFieldを描画
         *
         * \param val 入力した値が入るポインタ変数
         * \param label InputFieldのラベル
         * \param field_width InputFieldの幅 何も入れない or 0以下はデフォルト幅になる
         */
        bool Draw(std::vector<std::any> propertie, float field_width = 0);

    private:
        bool Bool3View(utility::Bool3* value, const char* name);
        bool Vector3View(utility::Vector3* value, const char* name);
        bool IntView(int* value, const char* name);
        bool FloatView(float* value, const char* name);
        bool StringView(std::string* value, const char* name);
        bool BoolView(bool* value, const char* name);
        bool QuaternionView(std::shared_ptr<utility::Quaternion> value, const char* name);
    };
}
