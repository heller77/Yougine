#include "ComponentClassNames.h"

#include <memory>
#include <tinygltf/json.hpp>

#include "../Projects/Project.h"
#include <fstream>

std::shared_ptr<ComponentClassNames::ComponentClassNames> ComponentClassNames::ComponentClassNames::instance = nullptr;

ComponentClassNames::ComponentClassNames::ComponentClassNames()
{
    this->componentClassNames = {
            "yougine::components::DebugComponent", "yougine::components::TransformComponent",
            "yougine::components::RigidBodyComponent", "yougine::components::RenderComponent",
            "yougine::components::camera::CameraComponent"
    };
}

std::shared_ptr<ComponentClassNames::ComponentClassNames> ComponentClassNames::ComponentClassNames::GetInstance()
{
    if (instance == nullptr)
    {
        instance = std::make_shared<ComponentClassNames>();
    }
    return instance;
}

bool ComponentClassNames::ComponentClassNames::AddComponentName(std::string componentName)
{
    //既に追加されているか
    auto result = std::find(this->componentClassNames.begin(), this->componentClassNames.end(), componentName);
    if (result == this->componentClassNames.end())
    {
        this->componentClassNames.push_back(componentName);
        return true;
    }
    else
    {
        return false;
    }
}

std::vector<std::string> ComponentClassNames::ComponentClassNames::GetComponentClassNames()
{
    return this->componentClassNames;
}

void ComponentClassNames::ComponentClassNames::AddUserScriptNames()
{
    auto componentnameFile = projects::Project::GetInstance()->projectFolderPath + "/usercomponentnames.json";

    std::ifstream reading(componentnameFile, std::ios::in);
    using json = nlohmann::ordered_json;

    json o_json;
    reading >> o_json;
    auto nemasvec = o_json["name"].get<std::vector<std::string>>();
    for (const auto& name : nemasvec)
    {
        this->AddComponentName(name);
    }


}

