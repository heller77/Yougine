#pragma once

#include "../../../lib/tinygltf/json.hpp"
#include "../Scene.h"
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

    public:
        Scene* jb_scene;

    private:
        void InitializeScene(Scene* scene);
        void SetPropertiesToComponent(components::Component* component, nlohmann::basic_json<nlohmann::ordered_map> j_component);

    public:
        void CreateScene();
        void UpdateJsonObj(std::string filepath);
    };
}