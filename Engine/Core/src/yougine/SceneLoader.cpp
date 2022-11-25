#include "SceneLoader.h";

#include <tinygltf/json.hpp>

namespace yougine
{
    SceneLoader::SceneLoader()
    {
        //json‰Šú‰»‚Æ‚©‚·‚é
    }

    void SceneLoader::InitializeScene(Scene* scene)
    {
        for (std::string gameobject_name : scene_json)
        {
            GameObject* top_gameobject = scene->CreateGameObject(gameobject_name);

        }
    }

    void SceneLoader::RecursiveChildObjects(nlohmann::json j, GameObject* parent)
    {
        if (nlohmann::detail::input_format_t::json != nlohmann::detail::value_t::null)
        {
            GameObject* obj =
        }
    }


}
