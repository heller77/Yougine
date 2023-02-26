#include "pch.h"

#include "yougine/components/TransformComponent.h"


TEST(Quaternion, QuaternionTest1)
{
    utility::Vector3 euler = utility::Vector3(10, 0, 0);
    auto quaternion = utility::Quaternion::GenerateQuartanionFromEuler(euler.x,euler.y,euler.z);
    auto quarternionEuler = quaternion->CalculateEuler();


    EXPECT_FLOAT_EQ(euler.x, quarternionEuler.x);
    EXPECT_FLOAT_EQ(euler.y, quarternionEuler.y);
    EXPECT_FLOAT_EQ(euler.z, quarternionEuler.z);
}
TEST(Quaternion, QuaternionTest2)
{
    utility::Vector3 euler = utility::Vector3(60, 60, 0);
    auto quaternion = utility::Quaternion::GenerateQuartanionFromEuler(euler.x, euler.y, euler.z);
    auto quarternionEuler = quaternion->CalculateEuler();


    EXPECT_FLOAT_EQ(euler.x, quarternionEuler.x);
    EXPECT_FLOAT_EQ(euler.y, quarternionEuler.y);
    EXPECT_FLOAT_EQ(euler.z, quarternionEuler.z);
}
TEST(Quaternion, QuaternionTest3)
{
    utility::Vector3 euler = utility::Vector3(90, 90, 0);
    auto quaternion = utility::Quaternion::GenerateQuartanionFromEuler(euler.x, euler.y, euler.z);
    auto quarternionEuler = quaternion->CalculateEuler();


    EXPECT_FLOAT_EQ(euler.x, quarternionEuler.x);
    EXPECT_FLOAT_EQ(euler.y, quarternionEuler.y);
    EXPECT_FLOAT_EQ(euler.z, quarternionEuler.z);
}

TEST(Quaternion, QuaternionTest4)
{
    utility::Vector3 euler = utility::Vector3(100, 100, 0);
    auto quaternion = utility::Quaternion::GenerateQuartanionFromEuler(euler.x, euler.y, euler.z);
    auto quarternionEuler = quaternion->CalculateEuler();


    EXPECT_FLOAT_EQ(euler.x, quarternionEuler.x);
    EXPECT_FLOAT_EQ(euler.y, quarternionEuler.y);
    EXPECT_FLOAT_EQ(euler.z, quarternionEuler.z);
}
