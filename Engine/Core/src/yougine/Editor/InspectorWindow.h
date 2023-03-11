#pragma once
#include "EditorWindow.h"
#include "../InputManager.h"
#include "ComponentViewer.h"
#include "../component_factory/ComponentFactory.h"
#include "InspectorWindows/AssetView/view/AssetView.h"

namespace editor
{
    class InspectorWindow : public EditorWindow
    {
    private:
        yougine::Scene* scene;
        yougine::InputManager* input_manager;
        SelectionInfo* selection_info;
        yougine::LayerManager* layer_manager;
        const int MAX_SIZE_OBJ_NAME = 38;
        yougine::componentfactorys::ComponentFacotory* componentfactory;

        std::shared_ptr<AssetView::AssetView> asset_view;

    private:
        void ShowGameObjectData();
        void ShowAddComponentMenu();

        /**
         * \brief assetのパラメータを表示
         * \param asset
         */
        void ShowAssetParameter(std::shared_ptr<projectwindows::assets::elements::model::Asset> asset);

    public:
        InspectorWindow(EditorWindowsManager*, yougine::Scene*, yougine::InputManager*);
        ~InspectorWindow();

        //viewの再生成
        void ViewReGenerate();

        void Draw()override;
    };
}
