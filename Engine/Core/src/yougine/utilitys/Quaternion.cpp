#define _USE_MATH_DEFINES
#include "Quaternion.h"
#include <cmath>
#include <iostream>
#include <memory>

utility::Quaternion::~Quaternion()
{
    // std::cout << "delete quaternion" <<std::endl;
}

/**
 * \brief axisを軸としてradian回転したQuartanion生成
 * \param axis 軸
 * \param degree 軸に対する回転角度
 * \return 
 */
std::shared_ptr<utility::Quaternion> utility::Quaternion::GenerateQuartanionFromAngleAndAxis(Vector3 axis, float degree)
{
    //2rad回転してしまうので、1/2欠ける
    float half_rad = ((double)degree / 2.0f) * (M_PI / 180);
    float sin = std::sin(half_rad);
    float cos = std::cos(half_rad);
    auto returnvalue = std::make_shared<Quaternion>(sin * axis.x, sin * axis.y, sin * axis.z, cos);
    return returnvalue;
}

std::shared_ptr<utility::Quaternion> utility::Quaternion::GenerateQuartanionFromEuler(float x, float y, float z)
{
    //[cos(x/2)cos(y/2)cos(z/2)+sin(x/2)sin(y/2)sih(z/2),
    //sin(x/2)cos(y/2)cos(z/2)-cos(x/2)sin(y/2)sin(z/2),
    //cos(x/2)sin(y/2)cos(z/2)+sin(x/2)cos(y/2)sin(z/2),
    //cos(x/2)cos(y/2)sin(z/2)-sin(x/2)sin(y/2)cos(z/2)
    //]

    // float x_half_rad = x * (3.14f / 180) / 2;
    // float y_half_rad = y * (3.14f / 180) / 2;
    // float z_half_rad = z * (3.14f / 180) / 2;
    //
    // float xcos = std::cos(x_half_rad);
    // float xsin = std::sin(x_half_rad);
    //
    // float ycos = std::cos(y_half_rad);
    // float ysin = std::sin(y_half_rad);
    //
    // float zcos = std::cos(z_half_rad);
    // float zsin = std::sin(z_half_rad);
    //
    // auto q = new Quaternion(
    //
    //     xsin * ycos * zcos + xcos * ysin * zsin,
    //     xcos * ysin * zcos - xsin * ycos * zsin,
    //     xcos * ycos * zsin + xsin * ysin * zcos,
    //     xcos * ycos * zcos - xsin * ysin * zsin
    // );
    auto qx = *Quaternion::GenerateQuartanionFromAngleAndAxis(Vector3(1, 0, 0), x);
    auto qy = *Quaternion::GenerateQuartanionFromAngleAndAxis(Vector3(0, 1, 0), y);
    auto qz = *Quaternion::GenerateQuartanionFromAngleAndAxis(Vector3(0, 0, 1), z);
    auto qxqy = qy * qx;
    auto qxqy_qz = qxqy * qz;
    auto q = qz * qy * qx;
    // auto qx_axis = Quaternion::GenerateQuartanionFromAngleAndAxis(Vector3(1, 0, 0), x);
    auto returnvalue = std::make_shared<Quaternion>(q.x, q.y, q.z, q.w);

    return returnvalue;
}

glm::mat4 utility::Quaternion::ConvertToGlmMat4()
{
    glm::mat4 matrix(0.0);

    // matrix[0][0] = 1 - 2 * y * y - 2 * z * z;
    // matrix[0][1] = 2 * x * y + 2 * w * z;
    // matrix[0][2] = 2 * x * z - 2 * w * y;
    // matrix[0][3] = 0;
    //
    // matrix[1][0] = 2 * x * y - 2 * w * z;
    // matrix[1][1] = 1 - 2 * x * x - 2 * z * z;
    // matrix[1][2] = 2 * y * z + 2 * w * x;
    // matrix[1][3] = 0;
    //
    // matrix[2][0] = 2 * x * z + 2 * w * y;
    // matrix[2][1] = 2 * y * z - 2 * w * x;
    // matrix[2][2] = 1 - 2 * x * x - 2 * y * y;
    // matrix[2][3] = 0;
    //
    // matrix[3][0] = 0;
    // matrix[3][1] = 0;
    // matrix[3][2] = 0;
    // matrix[3][3] = 1;

    matrix[0][0] = 1 - 2 * y * y - 2 * z * z;
    matrix[0][1] = 2 * x * y + 2 * w * z;
    matrix[0][2] = 2 * x * z - 2 * w * y;
    matrix[0][3] = 0;

    matrix[1][0] = 2 * x * y - 2 * w * z;
    matrix[1][1] = 1 - 2 * x * x - 2 * z * z;
    matrix[1][2] = 2 * y * z + 2 * w * x;
    matrix[1][3] = 0;

    matrix[2][0] = 2 * x * z + 2 * w * y;
    matrix[2][1] = 2 * y * z - 2 * w * x;
    matrix[2][2] = 1 - 2 * x * x - 2 * y * y;
    matrix[2][3] = 0;

    matrix[3][0] = 0;
    matrix[3][1] = 0;
    matrix[3][2] = 0;
    matrix[3][3] = 1;

    return matrix;
}

utility::Quaternion utility::Quaternion::operator*(Quaternion& quat)
{
    //xw+yz-zy+wx
    float multiply_x = x * quat.w + y * quat.z - z * quat.y + w * quat.x;
    //-xz+yw+zx+wy
    float multiply_y = -x * quat.z + y * quat.w + z * quat.x + w * quat.y;
    //xy-yx+zw+wz
    float multiply_z = x * quat.y - y * quat.x + z * quat.w + w * quat.z;
    //-xx-yy-zz+ww
    float multiply_w = -x * quat.x - y * quat.y - z * quat.z + w * quat.w;

    return Quaternion(multiply_x, multiply_y, multiply_z, multiply_w);
}

std::shared_ptr<utility::Quaternion> utility::Quaternion::operator=(std::shared_ptr<utility::Quaternion> quat)
{
    this->x = quat->x;
    this->y = quat->y;
    this->z = quat->z;
    this->w = quat->w;
    std::cout << "operator=" << std::endl;
    return std::make_shared<Quaternion>(x, y, z, w);
}

utility::Quaternion utility::Quaternion::GetIdentify()
{
    return Quaternion(0, 0, 0, 1);
}

utility::Vector3 utility::Quaternion::CalculateEuler()
{
    float pi = M_PI;

    float euler_y = std::asin(-(2.0f * (x * z - y * w))) * 180 / pi;
    float euler_x = 0;
    float euler_z = 0;
    if (std::cos(euler_y) < 0.01 && std::cos(euler_y) > -0.01)
    {
        euler_x = 0;
        euler_z = std::atan(-((2*x*y -2*z*w)/(2*w*w+2*y*y-1)));
    }
    else
    {
        euler_x = std::atan2((2.0f * (y * z + x * w)), (2 * w * w + 2 * z * z - 1)) * 180 / pi;
        euler_z = std::atan2(2.0f * (x * y + z * w), 2 * w * w + 2 * x * x - 1) * 180 / pi;
    }
    // float euler_x = std::atan2((2.0f * (y * x + y * z)), (w * w - x * x - y * y + z * z)) * 180 / pi;
    // float euler_y = std::asin(2.0f * (w * y - x * z)) * 180 / pi;
    // float euler_z = std::atan((2.0f * (w * z - x * y) / (w * w + x * x - y * y - z * z))) * 180 / pi;

    // auto matrix = this->ConvertToGlmMat4();
    //
    // auto a = std::atan(-matrix[1][2]/matrix[2][2]);
    // float euler_x = std::atan(-matrix[1][2] / matrix[2][2]) * pi / 180;
    // float euler_y = std::asin(-matrix[0][2]) * pi / 180;
    // float euler_z = std::atan(-matrix[0][1]/ matrix[0][0])*pi/180;

    // float euler_x = std::atan2((2.0f * (w * x + y * z)) ,(1 - 2 * (x * x + y * y))) * 180/pi;
    // float euler_y = -pi / 2 + 2 * std::atan2(std::sqrt(1 + 2 * (w * y - x * z)) , std::sqrt(1 - 2 * (w * y - x * z))) * 180/pi;
    // float euler_z = std::atan2((2 * (w * z + x * y)) , (1 - 2 * (y * y + z * z))) * 180/pi;
    return Vector3(euler_x, euler_y, euler_z);
}

std::string utility::Quaternion::ToString()
{
    std::string tostringValue = "[" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + "," +
        std::to_string(w) + "]";
    return tostringValue;
}
