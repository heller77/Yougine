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
        managers::ComponentName component_name;

    private:
        void InitializeProperties();

    public:
        Component(managers::ComponentName componentname);
        ~Component();
        virtual void Excute();
        void InitializeOnPlayBack();
        bool operator==(const Component& rhs) const;
        GameObject* GetGameObject();
        void SetParentGameObject(GameObject* parent_gameobject);
        void SetThisComponentToComponentList(Scene* scene);
    };
}