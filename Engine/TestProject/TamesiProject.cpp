#include <iostream>
#include <any>
#include <fstream>

#include "../Core/lib/tinygltf/json.hpp"

int main()
{
    using json = nlohmann::ordered_json;
    // std::ifstream ifs("testScene.json", std::ios::in);
    //
    // auto j3 = json::parse(ifs);
    // std::cout << j3["Scene"]["Hierarchy"][1] << std::endl;
    json SceneJsonInstance;
    json SceneValue;//シーン
    SceneValue["Name"] = "testScene";

    json hierarchy = json::array();
    json gameobject_1;
    gameobject_1["name"] = "gameobject_1";

    json componentList;

    json transformComponent_g1;
    transformComponent_g1["ComponentType"] = "TransformComponent";
    json transformComponent_g1_property;
    transformComponent_g1_property["position"] = { {"x",0.1},{"y",0.2},{"z",0.3} };
    transformComponent_g1["property"] = transformComponent_g1_property;
    componentList[0] = transformComponent_g1;

    gameobject_1["componentlist"] = componentList;

    hierarchy[0] = gameobject_1;


    hierarchy[1]["name"] = "gameobject_2";

    SceneValue["Hierarchy"] = hierarchy;
    SceneJsonInstance["Scene"] = SceneValue;

    std::ofstream writing_file;
    std::string filename = "testScene.json";
    writing_file.open(filename, std::ios::out);
    writing_file << SceneJsonInstance.dump(2) << std::endl;
    writing_file.close();

}
