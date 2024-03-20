#include "SceneFileExporter.h"

#include <any>
#include <fstream>
#include <typeinfo>
#include <iostream>

#include "UserShare/components/Component.h"
#include "UserShare/utilitys/Split.h"
#include "UserShare/utilitys/YougineMath.h"

#include "../Editor/ProjectWindows/Assets/element/Model/Asset.h"

yougine::SceneFiles::SceneFileExporter::SceneFileExporter()
{
    std::cout << "scenefileexporter create " << std::endl;
}

void yougine::SceneFiles::SceneFileExporter::ScenefileExportFromScene(Scene* scene, std::string filepath)
{
    auto gameobject_list = scene->GetGameObjects();
    using json = nlohmann::ordered_json;
    json json_scene;
    json json_scene_nakami; //シーン
    json_scene_nakami["Name"] = "testScene";

    json json_hierarchy = json::array();
    json json_gameobject_list;

    const std::string key_valuename = "name";
    const std::string key_of_valuetype = "type";
    int gamebject_index = 0;
    //ゲームオブジェクト
    for (auto gameobject : gameobject_list)
    {
        auto gameojbect_name = gameobject->GetName();
        json json_gameobject;
        json_gameobject["name"] = gameojbect_name;
        json json_componentlist;

        auto componentlist = gameobject->GetComponents();
        int componentindex = 0;
        for (auto component : componentlist)
        {
            auto componenttype = std::string(typeid(*component).name());
            componenttype = componenttype.substr(6);//冒頭の"class "を削除
            std::cout << "componenttype" << componenttype << std::endl;
            /// <summary>
            /// 一個分のコンポーネントのjson
            /// </summary>
            /// <returns></returns>
            json json_component;
            json_component["ComponentType"] = componenttype;

            auto serialize_property_list = component->GetAccessablePropertiesList();
            json json_propertylist;
            int property_index = 0;
            for (auto property_list : serialize_property_list)
            {
                auto var = property_list[0];
                auto valuename = std::any_cast<const char*>(property_list[1]);
                std::cout << "valuename : " << valuename << std::endl;
                json tmp_property_json;
                if (var.type() == typeid(int*))
                {
                    std::cout << "int " << std::endl;
                    auto value = std::any_cast<int*>(var);
                    std::cout << *value << std::endl;
                    tmp_property_json["value"] = *value;
                    json_propertylist[property_index][key_of_valuetype] = "int";
                }
                if (var.type() == typeid(float*))
                {
                    std::cout << "float " << std::endl;
                    auto value = std::any_cast<float*>(var);
                    std::cout << *value << std::endl;
                    tmp_property_json["value"] = *value;
                    json_propertylist[property_index][key_of_valuetype] = "float";
                }
                if (var.type() == typeid(std::string*))
                {
                    std::cout << "string " << std::endl;
                    auto value = std::any_cast<std::string*>(var);
                    std::cout << *value << std::endl;
                    tmp_property_json["value"] = *value;
                    json_propertylist[property_index][key_of_valuetype] = "string";
                }
                if (var.type() == typeid(bool*))
                {
                    std::cout << "bool" << std::endl;
                    auto value = std::any_cast<bool*>(var);
                    std::cout << *value << std::endl;
                    tmp_property_json["value"] = *value;
                    json_propertylist[property_index][key_of_valuetype] = "bool";
                }
                if (typeid(var) == typeid(std::any))
                {
                    std::string type_name = var.type().name();
                    std::string str_type = utility::Split::SplitStr(utility::Split::SplitStr(var.type().name(), ' ')[1],
                        '::').back();

                    if (str_type == "Vector3")
                    {
                        auto value = std::any_cast<utility::Vector3*>(var);
                        std::cout << "x :" << value->x << std::endl;
                        std::cout << "y :" << value->y << std::endl;
                        std::cout << "z :" << value->z << std::endl;
                        tmp_property_json["x"] = value->x;
                        tmp_property_json["y"] = value->y;
                        tmp_property_json["z"] = value->z;
                        json_propertylist[property_index][key_of_valuetype] = "utility::Vector3";
                    }

                    //sharedptrかどうか
                    auto template_start_pos = type_name.find("<");
                    if (template_start_pos != std::string::npos)
                    {
                        //最後の>
                        auto template_end_pos = type_name.rfind(">");
                        auto templatename = type_name.substr(template_start_pos + 1, template_end_pos - template_start_pos - 1);
                        if (templatename == "class editor::projectwindows::assets::elements::model::Asset")
                        {
                            auto value = std::any_cast<std::shared_ptr<editor::projectwindows::assets::elements::model::Asset>>(var);
                            auto id = value->GetAssetId()->convertstring();
                            tmp_property_json["value"] = id;
                            json_propertylist[property_index][key_of_valuetype] = "Asset";
                        }
                    }

                }
                json_propertylist[property_index][key_valuename] = valuename;
                json_propertylist[property_index]["values"] = tmp_property_json;
                property_index++;
                std::cout << std::endl;
            }
            json_component["property"] = json_propertylist;
            json_componentlist[componentindex++] = json_component;
        }
        json_gameobject["componentlist"] = json_componentlist;
        std::cout << "gameobject index" << gamebject_index << std::endl;
        std::cout << json_gameobject.dump(2) << std::endl;
        json_gameobject_list[gamebject_index++] = json_gameobject;
    }

    json_scene_nakami["Hierarchy"] = json_gameobject_list;
    json_scene["Scene"] = json_scene_nakami;


    std::ofstream writing_file(filepath);
    if (!writing_file)
    {
        std::cout << "scene export Failed !!" << std::endl;
    }
    else {
        // writing_file.open(filepath, std::ios::out);
        writing_file << json_scene.dump(2) << std::endl;
        writing_file.close();
    }
}

