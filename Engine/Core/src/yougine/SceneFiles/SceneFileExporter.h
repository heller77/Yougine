#pragma once
#include <string>



#include "UserShare/Scene.h"
#include "../../../lib/tinygltf/json.hpp"
using json = nlohmann::ordered_json;
/**
 * \brief シーンファイルを出力するクラス
 */
namespace yougine::SceneFiles
{
    class SceneFileExporter
    {
        //test
    public:
        SceneFileExporter();

        /**
         * \brief シーンクラスのインスタンスを元にSceneの情報をもつjsonファイルを出力
         * \param scene 対象のSceneインスタンス
         * \param filepath 出力するファイルパス
         */
        void ScenefileExportFromScene(Scene* scene, std::string filepath);
    };
}
