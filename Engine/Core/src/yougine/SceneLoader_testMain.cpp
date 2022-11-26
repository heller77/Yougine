///*
// * main.cppコメントアウトしてこれのコメントアウト外すと動く
// *
// * 1. JSONファイルを読み込む
// * 2. シーンのインスタンスを作成
// * 3. ゲームオブジェクトインスタンスを作成
// *      3.1. 各ゲームオブジェクトが持っているコンポーネントインスタンスを作成
// *          3.1.1. 各コンポーネントが持っているプロパティの値をセット
// *
// *  今回のテストコードでは名前が"testgameobject"のゲームオブジェクトが持つDebugComponentのプロパティを出力している
// */
//
//#include "SceneFiles/SceneLoader.h"
//
//int main()
//{
//    std::string filepath = "./testScene.json";
//
//    yougine::SceneFiles::SceneLoader* scene_loader = new yougine::SceneFiles::SceneLoader();
//
//    scene_loader->UpdateJsonObj(filepath);
//    scene_loader->CreateScene();
//
//    yougine::GameObject* obj = scene_loader->jb_scene->GetGameObjectByName("testgameobject1");
//    yougine::components::Component* component = obj->GetComponent<yougine::components::DebugComponent>();
//
//    std::vector<std::vector<std::any>> ap = component->GetAccessablePropertiesList();
//
//    std::cout << std::any_cast<int>(ap[0][0]) << std::endl;
//    std::cout << std::any_cast<int>(ap[1][0]) << std::endl;
//    std::cout << std::any_cast<float>(ap[2][0]) << std::endl;
//    //std::cout << std::any_cast<utility::Vector3>(ap[3][0]) << std::endl;
//    std::cout << std::any_cast<std::string>(ap[4][0]) << std::endl;
//    std::cout << std::any_cast<bool>(ap[5][0]) << std::endl;
//}
