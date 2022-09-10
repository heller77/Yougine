#pragma once
#include "../Scene.h"
#include "../managers/ComponentName.h"

namespace yougine
{
    class GameObject;
}
namespace yougine::components
{
    class Component
    {
    private:
        GameObject* parent_gameobject;

    private:
        void InitializeProperties();

    public:
        Component();
        ~Component();
        virtual void Excute();
        void InitializeOnPlayBack();
        bool operator==(const Component& rhs) const;
        GameObject* GetGameObject();
    };
}