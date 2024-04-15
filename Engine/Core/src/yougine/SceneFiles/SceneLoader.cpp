#include "SceneLoader.h"

#include "../component_factory/ComponentFactory.h"
#include "../Projects/Project.h"

namespace yougine::SceneFiles
{
    Scene* SceneLoader::InitializeScene(Scene* scene)
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
                auto componennt = componentfactory->CreateComponent(c["ComponentType"]);
                new_object->AddComponent(componennt);
                SetPropertiesToComponent(componennt, c);
                // std::cout <<"create component : " << c["ComponentType"] << std::endl;
                // std::vector<std::vector<std::any>>* accessable_properties_list = componennt->GetPtrAccessablePropertiesList();
                // std::cout<< std::any_cast<int*>( accessable_properties_list[0])<<std::endl;

            }
        }
        return scene;
    }


    Scene* SceneLoader::CreateScene()
    {
        std::string scene_name = obj_json["Scene"]["Name"];
        Scene* scene = new Scene(scene_name);

        InitializeScene(scene);
        return scene;
    }

    //シーンをリセットする（関数名updateよりresetかも）
    void SceneLoader::SceneUpdate(Scene* scene)
    {
        auto gameobjects = scene->GetGameObjects();
        for (int i = 0; i < gameobjects.size(); i++)
        {
            auto gameobjects = scene->GetGameObjects();
            auto gameobject = gameobjects.back();
            scene->RemoveGameObjcect(gameobject);
        }

        InitializeScene(scene);
    }

    void SceneLoader::SetPropertiesToComponent(components::Component* component, nlohmann::basic_json<nlohmann::ordered_map> j_component)
    {
        std::vector<std::vector<std::any>>* accessable_properties_list = component->GetPtrAccessablePropertiesList();
        int apl_indesx = 0;
        for (nlohmann::basic_json<nlohmann::ordered_map> p : j_component["property"])
        {
            if (p["type"] == "int")
            {
                int value = p["values"]["value"].get<int>();
                // int* pa = &value;
                // (*accessable_properties_list)[apl_indesx][0] = pa;
                (*std::any_cast<int*>((*accessable_properties_list)[apl_indesx][0])) = value;
                // std::cout << (*std::any_cast<int*>((*accessable_properties_list)[apl_indesx][0])) << std::endl;
                // std::cout << (*std::any_cast<int*>((*component->GetPtrAccessablePropertiesList())[apl_indesx][0])) << std::endl;

            }
            if (p["type"] == "float")
            {
                float value = p["values"]["value"].get<float>();
                // (*accessable_properties_list)[apl_indesx][0] = &value;
                (*std::any_cast<float*>((*accessable_properties_list)[apl_indesx][0])) = value;
            }
            if (p["type"] == "utility::Vector3")
            {
                utility::Vector3 vec3 = utility::Vector3(p["values"]["x"].get<float>(), p["values"]["y"].get<float>(), p["values"]["z"].get<float>());
                // (*accessable_properties_list)[apl_indesx][0] = vec3;
                (*std::any_cast<utility::Vector3*>((*accessable_properties_list)[apl_indesx][0])).x = vec3.x;
                (*std::any_cast<utility::Vector3*>((*accessable_properties_list)[apl_indesx][0])).y = vec3.y;
                (*std::any_cast<utility::Vector3*>((*accessable_properties_list)[apl_indesx][0])).z = vec3.z;
            }
            if (p["type"] == "string")
            {
                std::string value = p["values"]["value"].get<std::string>();
                // (*accessable_properties_list)[apl_indesx][0] = &value;
                (*std::any_cast<std::string*>((*accessable_properties_list)[apl_indesx][0])) = value;
            }
            if (p["type"] == "bool")
            {
                bool value = p["values"]["value"].get<bool>();
                // (*accessable_properties_list)[apl_indesx][0] = &value;
                (*std::any_cast<bool*>((*accessable_properties_list)[apl_indesx][0])) = value;
            }
            else if (p["type"] == "Asset")
            {
                std::string id = p["values"]["value"].get<std::string>();
                auto func = (std::any_cast<std::function<void(std::shared_ptr<editor::projectwindows::assets::elements::model::Asset>)>>((*accessable_properties_list)[apl_indesx][2]));
                func(projects::Project::GetInstance()->GetDataBase()->GetAsset(id));
            }
            apl_indesx++;
        }
    }

    SceneLoader::SceneLoader(std::string scenefilepath)
    {
        std::ifstream reading(scenefilepath, std::ios::in);

        json o_json;
        reading >> o_json;

        obj_json = o_json;
    }
}
