#pragma once

#include "tinygltf/json.hpp"
#include "UserShare/Scene.h"
#include <fstream>
#include "../components/DebugComponent.h"
#include "UserShare/utilitys/YougineMath.h"

using json = nlohmann::ordered_json;

namespace yougine::SceneFiles
{
    class SceneLoader
    {
    private:
        json obj_json;

    private:
        Scene* InitializeScene(Scene* scene);
        void SetPropertiesToComponent(components::Component* component, nlohmann::basic_json<nlohmann::ordered_map> j_component);

    public:
        SceneLoader(std::string scenefilepath);
        Scene* CreateScene();
        void SceneUpdate(Scene* scene);

    };
}