#include "SceneLoader.h"

#include "../component_factory/ComponentFactory.h"

namespace yougine::SceneFiles
{
    void SceneLoader::InitializeScene(Scene* scene)
    {
        for (nlohmann::basic_json<nlohmann::ordered_map> e : obj_json["Scene"]["Hierarchy"])
        {
            GameObject* parent_gameobject = nullptr;
            GameObject* new_object = scene->CreateGameObject(e["name"], parent_gameobject);
            for (nlohmann::basic_json<nlohmann::ordered_map> c : e["componentlist"])
            {
                // if (c["ComponentType"] == "yougine::components::DebugComponent")
                // {
                //     new_object->AddComponent(new yougine::components::DebugComponent());
                //     components::Component* component = new_object->GetComponent<yougine::components::DebugComponent>();
                //
                //     SetPropertiesToComponent(component, c);
                // }
                // if (c["ComponentType"] == "yougine::components::TransformComponent")
                // {
                //     //こんな感じでコンポーネント全列挙（コードジェネレート使うと思う）
                // }
                auto componentfactory = new componentfactorys::ComponentFacotory();
                auto componennt=componentfactory->CreateComponent(c["ComponentType"]);
                new_object->AddComponent(componennt);
                SetPropertiesToComponent(componennt, c);

            }
        }
    }


    void SceneLoader::CreateScene()
    {
        std::string scene_name = obj_json["Scene"]["Name"];
        Scene* scene = new Scene(scene_name);

        jb_scene = scene;

        InitializeScene(scene);
    }

    void SceneLoader::UpdateJsonObj(std::string filepath)
    {
        std::ifstream reading(filepath, std::ios::in);

        json o_json;
        reading >> o_json;

        obj_json = o_json;
    }

    void SceneLoader::SetPropertiesToComponent(components::Component* component, nlohmann::basic_json<nlohmann::ordered_map> j_component)
    {
        std::vector<std::vector<std::any>>* accessable_properties_list = component->GetPtrAccessablePropertiesList();
        int apl_indesx = 0;
        for (nlohmann::basic_json<nlohmann::ordered_map> p : j_component["property"])
        {
            if (p["type"] == "int")
            {
                (*accessable_properties_list)[apl_indesx][0] = p["values"]["value"].get<int>();
            }
            if (p["type"] == "float")
            {
                (*accessable_properties_list)[apl_indesx][0] = p["values"]["value"].get<float>();
            }
            if (p["type"] == "utility::Vector3")
            {
                utility::Vector3 vec3 = utility::Vector3(p["values"]["x"].get<float>(), p["values"]["y"].get<float>(), p["values"]["z"].get<float>());
                (*accessable_properties_list)[apl_indesx][0] = vec3;
            }
            if (p["type"] == "string")
            {
                (*accessable_properties_list)[apl_indesx][0] = p["values"]["value"].get<std::string>();
            }
            if (p["type"] == "bool")
            {
                (*accessable_properties_list)[apl_indesx][0] = p["values"]["value"].get<bool>();
            }
            apl_indesx++;
        }
    }



}
