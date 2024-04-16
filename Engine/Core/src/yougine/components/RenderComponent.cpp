#include "RenderComponent.h"
#include "./../managers/RenderManager.h"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "../managers/ComponentExportParameterManager.h"
#include "../Projects/Project.h"
#include "tinygltf/tiny_gltf.h"

namespace yougine::components
{
    RenderComponent::RenderComponent() : Component(components::ComponentName::kRender), program(0), vao(0)
    {
        namespace materials = editor::projectwindows::assets::elements::model::materials;

        //露出するパラメータ("2342161b-f95e-4c2f-81fb-f21fe464712a"はデフォルトで用意しているマテリアルのアセットID)
        //materialを初期化、エディタに露出するように設定
        material = std::dynamic_pointer_cast<materials::Material>(projects::Project::GetInstance()->GetDataBase()->GetAsset("2342161b-f95e-4c2f-81fb-f21fe464712a"));
        auto asset_cast = static_cast<std::shared_ptr<editor::projectwindows::assets::elements::model::Asset>>(material);
        std::function<void(std::shared_ptr<assetnamespace::Asset>)> material_change_function =
            managers::ComponentExportParameterManager::Generate_AssetTypeField_Switch_Function(
                this, &material, GETVALUENAME(material));
        std::function<void(std::shared_ptr<assetnamespace::Asset>)> materialsetfunction = [=](std::shared_ptr<assetnamespace::Asset> input) {
            std::cout << "material change" << std::endl;
            material_change_function(input);
            Initialize();
        };
        accessable_properties_list.emplace_back(std::vector<std::any>{asset_cast, GETVALUENAME(material), materialsetfunction});


        //meshを露出
        this->mesh_asset
            = std::dynamic_pointer_cast<editor::projectwindows::assets::elements::model::mesh::MeshAsset>(
                projects::Project::GetInstance()->GetDataBase()->GetAsset("f9ad467e-3e2f-41fd-a2a1-9d313c1d0c88"));
        auto mesh_asset_cast = static_cast<std::shared_ptr<editor::projectwindows::assets::elements::model::Asset>>(mesh_asset);

        std::function<void(std::shared_ptr<assetnamespace::Asset>)> mesh_change_function =
            managers::ComponentExportParameterManager::Generate_AssetTypeField_Switch_Function(
                this, &mesh_asset, GETVALUENAME(mesh_asset));
        std::function<void(std::shared_ptr<assetnamespace::Asset>)> meshsetfunction = [=](std::shared_ptr<assetnamespace::Asset> input) {
            std::cout << "mesh change" << std::endl;
            mesh_change_function(input);
            Initialize();
        };
        accessable_properties_list.emplace_back(std::vector<std::any>{mesh_asset_cast, GETVALUENAME(mesh_asset), meshsetfunction});


        // GLuint program, vao;
        // program = yougine::managers::RenderManager::ShaderInitFromFilePath(
        //     "./Resource/shader/test.vert", "./Resource/shader/test.frag");
        program = yougine::managers::RenderManager::ShaderInitFromFilePath(this->material->GetVertexShader(), this->material->GetFragmentShader());
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        // this->SetProgram(program);
        // this->SetVao(vao);

        InitializeMesh();



    }
    void RenderComponent::ShaderCompile()
    {

    }

    void RenderComponent::InitializeMesh()
    {
        tinygltf::Model model;
        tinygltf::TinyGLTF loader;
        std::string err, warn;
        // bool ret = loader.LoadASCIIFromFile(&model, &err, &warn, "./Resource/Mesh/cube/cube.gltf");
        auto gltffilepath = this->mesh_asset->GetFilePath();
        bool ret = loader.LoadASCIIFromFile(&model, &err, &warn, gltffilepath.string());
        std::cout << "scene length" << model.scenes.size() << std::endl;
        auto scene = model.scenes[0];
        auto nodeindex = scene.nodes[0]; //シーンの参照しているのノード（本当は複数あるパターンにも対応すべき）
        auto node = model.nodes[nodeindex];
        auto mesh = model.meshes[node.mesh];
        auto position_index = mesh.primitives[0].attributes["POSITION"]; //accessorのインデックス
        auto indices_index = mesh.primitives[0].indices; //accessorのインデックス
        auto position_accessor = model.accessors[position_index];

        auto buffer_views = model.bufferViews;

        auto position_buffer_view = buffer_views[position_accessor.bufferView];
        auto position_buffer = model.buffers[position_buffer_view.buffer];
        const float* positions = reinterpret_cast<const float*>(&position_buffer.data[position_buffer_view.byteOffset +
            position_accessor.byteOffset]);
        std::cout << "position buffer data" << std::endl;
        //頂点座標をvertex_vectorに追加
        this->vertex_vector = {};
        for (size_t i = 0; i < position_accessor.count; ++i)
        {
            // std::cout << i << "番目 : " << "[" << positions[i * 3 + 0] << "," << positions[i * 3 + 1] << "," << positions[
            //     i * 3 + 2] << "]" << std::endl;
            ShaderVector4 v = { positions[i * 3 + 0], positions[i * 3 + 1], positions[i * 3 + 2], 1 };
            this->vertex_vector.push_back(v);
        }
        auto indices_accessor = model.accessors[indices_index];
        auto indices_buffer_view = buffer_views[indices_accessor.bufferView];
        auto indices_buffer = model.buffers[indices_buffer_view.buffer];
        const unsigned short* indices_data_fromgltf = reinterpret_cast<const unsigned short*>(&indices_buffer.data[
            indices_buffer_view.byteOffset + indices_accessor.byteOffset]);
        std::cout << "index buffer data" << std::endl;
        //インデックスをindex_vectorに追加
        this->index_vector = {};
        for (size_t i = 0; i < indices_accessor.count; ++i)
        {
            // std::cout << i << "番目 : " << "[" << indices_data_fromgltf[i] << "]" << std::endl;
            this->index_vector.push_back(indices_data_fromgltf[i]);
        }

        //法線　読みだす
        auto normal_accessors_index = mesh.primitives[0].attributes["NORMAL"];
        auto normal_accessor = model.accessors[normal_accessors_index];
        auto normal_buffer_view = buffer_views[normal_accessor.bufferView];
        auto normal_buffer = model.buffers[normal_buffer_view.buffer];
        const float* normal_data_fromgltf = reinterpret_cast<const float*>(&normal_buffer.data[
            normal_buffer_view.byteOffset + normal_accessor.byteOffset]);

        std::vector<ShaderVector3> normal_vector = {};
        for (size_t i = 0; i < normal_accessor.count; ++i)
        {
            // std::cout << i << "番目 : " << "[" << indices_data_fromgltf[i] << "]" << std::endl;
            ShaderVector3 v = { normal_data_fromgltf[i * 3 + 0], normal_data_fromgltf[i * 3 + 1], normal_data_fromgltf[i * 3 + 2] };
            normal_vector.push_back(v);
        }


        std::cout << std::endl;
        std::cout << "buffer num " << model.buffers[0].data.size() << std::endl;

        auto positioncomponenttype = position_accessor.componentType;

        std::cout << "scene node : " << node.mesh << std::endl;

        auto position_point_count = position_accessor.count;
        //頂点バッファを作成
        // GLuint vertexBuffer;
        glGenBuffers(1, &this->vbolist.vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, this->vbolist.vertexBuffer);
        auto vertex = this->vertex_vector;
        glBufferData(GL_ARRAY_BUFFER, position_point_count * sizeof(ShaderVector4), vertex.data(), GL_STATIC_DRAW);
        auto vertexShader_PositionAttribute = glGetAttribLocation(program, "position");
        glEnableVertexAttribArray(vertexShader_PositionAttribute);
        glVertexAttribPointer(vertexShader_PositionAttribute, 4, GL_FLOAT, GL_FALSE, 0, 0);

        // //インデックスバッファ
        // GLuint elementBuffer;
        glGenBuffers(1, &this->vbolist.elementBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->vbolist.elementBuffer);
        auto indices = this->index_vector;
        auto indeicesSize = indices.size() * sizeof(indices[0]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indeicesSize, indices.data(), GL_STATIC_DRAW);

        managers::RenderManager::geterror("InitializeMesh() ");

        //法線バッファ
        // GLuint normalBuffer;
        glGenBuffers(1, &this->vbolist.normalBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, this->vbolist.normalBuffer);
        glBufferData(GL_ARRAY_BUFFER, normal_vector.size() * sizeof(ShaderVector3), normal_vector.data(), GL_STATIC_DRAW);
        managers::RenderManager::geterror("InitializeMesh() ");

        //シェーダに値を渡す
        auto vertexshader_normal_attribute = glGetAttribLocation(program, "normal");

        managers::RenderManager::geterror("InitializeMesh() glGetAttribLocation ");

        if (vertexshader_normal_attribute > 0) {
            glEnableVertexAttribArray(vertexshader_normal_attribute);
            managers::RenderManager::geterror("InitializeMesh() glEnableVertexAttribArray");

            glVertexAttribPointer(vertexshader_normal_attribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
            managers::RenderManager::geterror("InitializeMesh() glVertexAttribPointer");
        }
        this->draw_point_count = indices_accessor.count;
        managers::RenderManager::geterror("InitializeMesh() ");


    }

    void RenderComponent::Initialize()
    {
        if (this->program) { // 既存のプログラムがあれば削除
                // glDeleteProgram(this->program);
            program = -1;
        }
        managers::RenderManager::geterror("RenderComponent() ");

        if (this->vao)
        {
            glBindVertexArray(0);
            vao = -1;
        }
        managers::RenderManager::geterror("RenderComponent() ");


        this->vbolist.Release();
        managers::RenderManager::geterror("RenderComponent() ");


        program = yougine::managers::RenderManager::ShaderInitFromFilePath(this->material->GetVertexShader(), this->material->GetFragmentShader());
        managers::RenderManager::geterror("RenderComponent() ");

        glGenVertexArrays(1, &vao);
        managers::RenderManager::geterror("RenderComponent() ");

        glBindVertexArray(vao);
        managers::RenderManager::geterror("RenderComponent() ");

        InitializeMesh();
        managers::RenderManager::geterror("RenderComponent() ");
    }

    void RenderComponent::SetProgram(GLuint program)
    {
        this->program = program;
    }

    void RenderComponent::SetVao(GLuint vao)
    {
        this->vao = vao;
    }

    GLuint RenderComponent::GetProgram() const
    {
        return program;
    }

    GLuint RenderComponent::GetVao() const
    {
        return vao;
    }

    std::vector<ShaderVector4> RenderComponent::GetVertexVector() const
    {
        return vertex_vector;
    }

    void RenderComponent::SetVertexVector(const std::vector<ShaderVector4>& vertex_vector)
    {
        this->vertex_vector = vertex_vector;
    }

    std::vector<GLuint> RenderComponent::GetIndexVector() const
    {
        return index_vector;
    }

    void RenderComponent::SetIndexVector(const std::vector<GLuint>& index_vector)
    {
        this->index_vector = index_vector;
    }

    std::shared_ptr<editor::projectwindows::assets::elements::model::materials::Material> RenderComponent::GetMaterial()
    {
        return this->material;
    }


}
