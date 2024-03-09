#pragma once
#include <memory>
#include <string>

#include "glm/glm.hpp"

#include "UserShare/utilitys/YougineMath.h"

namespace utility
{
    class Quaternion
    {

    public:
        /// <summary>
        /// xyzが虚部,wが実部
        /// </summary>
        float x, y, z, w;

        Quaternion(float x, float y, float z, float w)
            : x(x),
            y(y),
            z(z),
            w(w)
        {
        }
        ~Quaternion();
        static std::shared_ptr<utility::Quaternion> GenerateQuartanionFromAngleAndAxis(Vector3 axis, float degree);

        static std::shared_ptr<utility::Quaternion> GenerateQuartanionFromEuler(float x, float y, float z);

        glm::mat4 ConvertToGlmMat4();

        Quaternion operator*(Quaternion& quat);
        std::shared_ptr<utility::Quaternion> operator=(std::shared_ptr<utility::Quaternion> quat);
        // std::ostream& operator<<(std::ostream& stream, const Quaternion& value);
        static Quaternion GetIdentify();
        Vector3 CalculateEuler();
        std::string ToString();

    };
}
