#pragma once
namespace yougine
{
    struct Vector3
    {
    public:
        float x, y, z;

        Vector3(float x, float y, float z)
            : x(x),
            y(y),
            z(z)
        {
        }

        /**
         * \brief 代入演算子
         * \param v 代入する値あ
         * \return 代入された参照
         */
        Vector3& operator=(const Vector3& v)
        {
            this->x = v.x;
            this->y = v.y;
            this->z = v.z;
        }
    };

}