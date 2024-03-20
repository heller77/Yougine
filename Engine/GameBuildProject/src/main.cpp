
#include <iostream>
/*
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include <stdio.h>
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
*/

#include "Editor/EditorWindowsManager.h"
#include "Editor/HierarchyWindow.h"
#include "Editor/SceneWindow.h"
#include "Editor/InspectorWindow.h"

#include <fstream>

#include "UserShare/components/TransformComponent.h"
#include "Editor/ProjectWindows/ProjectWindow.h"
#include "UserShare/managers/ComponentList.h"
#include "components/DebugComponent.h"
#include "managers/GameManager.h"
#include "managers/RigidBodyManager.h"
#include "Projects/Project.h"
#include "SceneFiles/SceneFileExporter.h"
#include "SceneFiles/SceneLoader.h"

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main()
{
    auto project = projects::Project::GetInstance();
    // project->projectFolderPath = "D:\\Yougin\\";//プロジェクトパスを直書きしてるのでよろしくない
    // project->AssetInitialize();
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
    GLFWwindow* const window = glfwCreateWindow(1280, 720, "Oreno Game", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    if (window == NULL)
    {
        std::cerr << "Can't create GLFW window" << std::endl;
        return 1;
    }


    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        return 1;
    }

    GLint windowframebuffer;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &windowframebuffer);

    int gVCBWidth = 300;
    int gVCBHeight = 300;

    // yougine::Scene* scene = new yougine::Scene("Scene1");
    auto sceneloader = yougine::SceneFiles::SceneLoader();
    sceneloader.UpdateJsonObj(project->projectFolderPath + "\\build\\scene.json");
    sceneloader.CreateScene();
    yougine::Scene* scene = sceneloader.jb_scene;
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


    //Add Code
    yougine::InputManager* input_manager = new yougine::InputManager();
    // editor::EditorWindowsManager* editor_windows_manager = new editor::EditorWindowsManager();
    // editor_windows_manager->AddRenderWindow(new editor::HierarchyWindow(editor_windows_manager, scene, input_manager));
    // editor_windows_manager->AddRenderWindow(new editor::SceneWindow(editor_windows_manager, scene));
    // editor_windows_manager->AddRenderWindow(new editor::InspectorWindow(editor_windows_manager, scene, input_manager));
    // editor_windows_manager->AddRenderWindow(new editor::projectwindows::ProjectWindow(editor_windows_manager, scene));

    //GameManagerで回すマネージャのvector
    std::vector<IManager*> managerlist;
    auto componentlist = scene->GetComponentList();
    auto rigidbodymanager = new yougine::managers::RigidBodyManager(componentlist);
    managerlist.push_back(rigidbodymanager);
    //GameManagerを生成
    GameManager* game_manager = new GameManager(managerlist);
    std::cout << "this is game build" << std::endl;

    //render
    auto rendermanager = yougine::managers::RenderManager(1920, 1080, windowframebuffer, scene->GetComponentList());
    while (glfwWindowShouldClose(window) == GL_FALSE)
    {
        input_manager->UpdateInput();
        rendermanager.RenderScene();
        glfwSwapBuffers(window);
        glfwPollEvents();
        /*
        if (input_manager->IsPushKey(yougine::KeyBind::RightClick))
        {
            std::cout << "RightClick" << std::endl;
        }
        */

        //毎フレーム、マネージャ群のUpdate関数を呼び出す
        // game_manager->Update();

        // editor_windows_manager->CreateWindows(window);
    }
    //
    // ImGui_ImplOpenGL3_Shutdown();
    // ImGui_ImplGlfw_Shutdown();
    // ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}