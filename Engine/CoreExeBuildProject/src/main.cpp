
#include <iostream>
/*
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include <stdio.h>
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
*/

#include <direct.h>

#include "Editor/EditorWindowsManager.h"
#include "Editor/HierarchyWindow.h"
#include "Editor/SceneWindow.h"
#include "Editor/InspectorWindow.h"
#include "Editor/ShaderGraph/ShaderGraphWindow.h"

#include <fstream>

#include "UserShare/components/TransformComponent.h"
#include "Editor/ProjectWindows/ProjectWindow.h"
#include "UserShare/managers/ComponentList.h"
#include "components/DebugComponent.h"
#include "Editor/MenuBar.h"
#include "managers/RigidBodyManager.h"
#include "managers/GameManager.h"
#include "Projects/Project.h"
#include "SceneFiles/SceneFileExporter.h"
#include "SceneFiles/SceneLoader.h"
#include "UserShare/InputManager.h"

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main()
{

    auto project = projects::Project::GetInstance();
    //projectのパスを設定
    project->Initialize("./Resource/Project.json");

    glfwSetErrorCallback(glfw_error_callback);

    if (glfwInit() == GLFW_FALSE)
    {
        std::cerr << "Can't initialize GLFW" << std::endl;
        return 1;
    }

    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on Mac

    //�E�B���h�E���쐬
    GLFWwindow* const window = glfwCreateWindow(1280, 720, "Game Engine", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    if (window == NULL)
    {
        std::cerr << "Can't create GLFW window" << std::endl;
        return 1;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    ImNodes::CreateContext();

    // Setup Dear ImGui style
    //ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        return 1;
    }

    int gVCBWidth = 300;
    int gVCBHeight = 300;
    auto sceneloader = yougine::SceneFiles::SceneLoader();

    //シーンファイルのエクスポート（本来はeditor上の操作によりエクスポートしたい。
    //なんならビルド先にできるのおかしい。ビルド時にファイルコピーがされるべき）
    auto sceneexporter = new yougine::SceneFiles::SceneFileExporter();
    auto projectpath = projects::Project::GetInstance()->projectFolderPath;
    auto buildfolder = projectpath + "build\\";
    if (_mkdir(buildfolder.c_str())) {
        std::cout << "buildフォルダ作成" << std::endl;
    }
    //シーンファイルのパス
    std::string scenefilepath = project->projectFolderPath + "\\build\\scene.json";
    yougine::Scene* scene;
    FILE* fp;
    errno_t error;
    error = fopen_s(&fp, scenefilepath.c_str(), "r");

    if (error == 0)
    {
        //シーンファイルがあれば
        auto sceneloader = yougine::SceneFiles::SceneLoader();
        sceneloader.UpdateJsonObj(scenefilepath);
        sceneloader.CreateScene();
        scene = sceneloader.jb_scene;
        fclose(fp);
    }
    else
    {
        //シーンファイルが無ければ
        scene = new yougine::Scene("Scene1");

        int gVCBHeig3ht = 300;
        auto rendercomponent = new yougine::components::RenderComponent();
        auto gameobject = scene->CreateGameObject("renderObj_1", nullptr);
        gameobject->AddComponent(rendercomponent);
        gameobject->AddComponent(new yougine::components::TransformComponent(0, 0, 0));
        gameobject->AddComponent(new yougine::components::DebugComponent());
        auto gameobject2 = scene->CreateGameObject("renderObj_2", nullptr);
        gameobject2->AddComponent(new yougine::components::TransformComponent(1, 1, 1));
        yougine::SceneFiles::SceneFileExporter* exporter = new yougine::SceneFiles::SceneFileExporter();


        //カメラオブジェクトの生成
        auto camera = scene->CreateGameObject("Camera", nullptr);
        camera->AddComponent(new yougine::components::TransformComponent(10, 0, 0));
        camera->AddComponent(new yougine::components::camera::CameraComponent());

        //シーンファイルをエクスポート
        exporter->ScenefileExportFromScene(scene, scenefilepath);
    }

    // yougine::Scene* scene = new yougine::Scene("Scene1");
    //
    // int gVCBHeig3ht = 300;
    // //レンダーコンポーネントをAdd出来るかのコード（後で消す）
    // auto rendercomponent = new yougine::components::RenderComponent();
    // auto gameobject = scene->CreateGameObject("renderObj_1", nullptr);
    // gameobject->AddComponent(rendercomponent);
    // gameobject->AddComponent(new yougine::components::TransformComponent(0, 0, 0));
    //
    // gameobject->AddComponent(new yougine::components::DebugComponent());
    //
    //
    // std::cout << "gameobject has componet num " << gameobject->GetComponents().size() << std::endl;
    // auto gameobject2 = scene->CreateGameObject("renderObj_2", nullptr);
    // // gameobject2->AddComponent(new yougine::components::RenderComponent());
    // gameobject2->AddComponent(new yougine::components::TransformComponent(1, 1, 1));
    // // gameobject->AddComponent(new yougine::components::TransformComponent(0, 0, 0));




    // sceneexporter->ScenefileExportFromScene(scene, projectpath +"build\\scene.json");

    //Add Code
    yougine::InputManager* input_manager = new yougine::InputManager();
    editor::EditorWindowsManager* editor_windows_manager = new editor::EditorWindowsManager();
    editor_windows_manager->AddRenderWindow(new editor::HierarchyWindow(editor_windows_manager, scene, input_manager));
    editor_windows_manager->AddRenderWindow(new editor::SceneWindow(editor_windows_manager, scene));
    editor_windows_manager->AddRenderWindow(new editor::InspectorWindow(editor_windows_manager, scene, input_manager));
    editor_windows_manager->AddRenderWindow(new editor::projectwindows::ProjectWindow(editor_windows_manager, scene));
    auto menubar = new editor::MenuBar(editor_windows_manager, scene);
    editor_windows_manager->AddRenderWindow(menubar);
    editor_windows_manager->AddRenderWindow(new editor::shadergraph::ShaderGraphWindow(editor_windows_manager));
    //GameManagerで回すマネージャのvector
    std::vector<IManager*> managerlist;
    //auto componentlist = new yougine::managers::ComponentList();
    auto componentlist = scene->GetComponentList();
    // auto custommanager = new yougine::managers::CustomScriptManager(componentlist);
    auto rigidbodymanager = new yougine::managers::RigidBodyManager(componentlist);
    // managerlist.push_back(custommanager);
    managerlist.push_back(rigidbodymanager);
    //GameManagerを生成
    GameManager* game_manager = new GameManager(managerlist);

    //一フレーム前にPlayだったか
    bool preIsPlay = false;
    while (glfwWindowShouldClose(window) == GL_FALSE)
    {
        input_manager->UpdateInput();
        /*
        if (input_manager->IsPushKey(yougine::KeyBind::RightClick))
        {
            std::cout << "RightClick" << std::endl;
        }
        */

        //毎フレーム、マネージャ群のUpdate関数を呼び出す
        if (menubar->GetPlay()) {
            if (preIsPlay == false)
            {
                //プレイし始め最初
                scene->InitializeAllGameObjcts();
            }
            game_manager->Update();
            scene->Update();
        }
        preIsPlay = menubar->GetPlay();


        editor_windows_manager->CreateWindows(window);


    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    ImNodes::DestroyContext();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

}