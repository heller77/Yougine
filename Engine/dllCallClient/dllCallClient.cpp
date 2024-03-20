// dllCallClient.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include "UserShare/utilitys/Split.h"
#include "UserShare/utilitys/YougineMath.h"
#include "windows.h"
#include "UserShare/components/Component.h"
#include "UserShare/GameObject.h"
#include "UserShare/components/userscriptcomponents/IUpdatable.h"

typedef yougine::components::Component* (*FUNC1)();

int main()
{
    // std::cout << "main" << std::endl;
    //
    // std::string ore_sore = "ore,sore";
    // char elem = ',';
    //
    // auto hoge = utility::Split::SplitStr(ore_sore, elem);
    // std::cout << hoge[0] << " , " << hoge[1] << std::endl;
    //
    // utility::Vector3 vector3(1, 2, 3);
    // std::cout << vector3.x << " : " << vector3.y << " : " << vector3.z << std::endl;

    //todo: ファイルパスは一旦直
    HMODULE hModule = LoadLibrary(TEXT("D:/Yougin/userscriptBuild/Debug/MyNewDLLProject.dll"));
    if (!hModule) {
        std::cerr << "DLLをロードできませんでした。" << std::endl;
        return 1;
    }
    FUNC1 func1 = (FUNC1)GetProcAddress(hModule, "GenerateUserScriptComponent");

    auto scene = new yougine::Scene("tamesiScene");
    auto gameobjcet = scene->CreateGameObject("tamesi", nullptr);
    auto comp = func1();

    gameobjcet->AddComponent(comp);

    yougine::components::userscriptcomponents::IUpdatable* i_updatable = dynamic_cast<yougine::components::userscriptcomponents::IUpdatable*>(comp);
    i_updatable->Update();
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
