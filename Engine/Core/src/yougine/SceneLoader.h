#pragma once
#include <tinygltf/json.hpp>

#include "Scene.h"

namespace yougine
{
    class SceneLoader
    {
    private:
        //json
        nlohmann::json scene_json;

    private:
        void InitializeScene(Scene* scene);
        void RecursiveChildObjects(nlohmann::json, GameObject* parent);

    public:
        SceneLoader();
    };
}