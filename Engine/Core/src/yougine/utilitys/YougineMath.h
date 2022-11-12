#pragma once
namespace utility
{
    struct Vector2
    {
    public:
        float x, y, z;

        Vector2(float x, float y)
            : x(x),
            y(y)
        {
        }

        /**
         * \brief 代入演算子
         * \param v 代入する値あ
         * \return 代入された参照
         */
        Vector2& operator=(const Vector2& v)
        {
            this->x = v.x;
            this->y = v.y;
        }
    };

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

    struct Vector4
    {
    public:
        float x, y, z, w;

        Vector4(float x, float y, float z, float w)
            : x(x),
            y(y),
            z(z),
            w(w)
        {
        }

        /**
         * \brief 代入演算子
         * \param v 代入する値あ
         * \return 代入された参照
         */
        Vector4& operator=(const Vector4& v)
        {
            this->x = v.x;
            this->y = v.y;
            this->z = v.z;
            this->w = v.w;
        }
    };

    /**
     * \brief boolを3つ
     */
    struct Bool3
    {
    public:
        bool x, y, z;
        Bool3(bool x, bool y, bool z)
            : x(x),
            y(y),
            z(z)
        {
        }
    };
}