////SceneExportを試すmain.cpp(普通のmain.cppをコメントアウトしてこっちのコメントを外せば動かせる。)
//
//
//#include <fstream>
//#include <typeinfo>
//#include <string>
//
//#include "Scene.h"
//#include "components/DebugComponent.h"
//#include "components/TransformComponent.h"
//#include "SceneFiles/SceneFileExporter.h"
//#include "tinygltf/json.hpp"
//// #include "../Core/src/yougine/Scene.h"
//
//int main()
//{
//    yougine::Scene* sceme = new yougine::Scene("test");
//    auto testgameobject1 = sceme->CreateGameObject("testgameobject1", nullptr);
//    // sceme->CreateGameObject("testgameobject2", nullptr);
//    // testgameobject1->AddComponent(new yougine::components::TransformComponent(0, 0, 0));
//    testgameobject1->AddComponent(new yougine::components::DebugComponent());
//    // testgameobject1->AddComponent(new yougine::components::DebugComponent());
//
//    yougine::SceneFiles::SceneFileExporter* sceneexporter = new yougine::SceneFiles::SceneFileExporter();
//    sceneexporter->ScenefileExportFromScene(sceme, "./testScene.json");
//
//}
