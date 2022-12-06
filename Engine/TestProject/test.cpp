#include "pch.h"

#include "yougine/components/TransformComponent.h"


TEST(TransformComponent, TestName)
{
    auto transformcomponent = new yougine::components::TransformComponent(1, 1, 1);
    EXPECT_EQ(3, transformcomponent->GetPosition().y);
    EXPECT_TRUE(true);
}
TEST(TransformComponent, TestName2)
{
    auto transformcomponent = new yougine::components::TransformComponent(1, 3, 1);
    EXPECT_EQ(3, transformcomponent->GetPosition().y);
    EXPECT_TRUE(true);
}
