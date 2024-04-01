# DLLを作成するために必要なCMakeの最小バージョンを指定
cmake_minimum_required(VERSION 3.0)

# ライブラリのプロジェクト名を定義
project(UserEngineCommon)

# srcフォルダー以下のcppファイル一覧をcppfilesという変数に格納
file(GLOB_RECURSE cppfiles RELATIVE ${PROJECT_SOURCE_DIR} ./include/*.cpp)

# DLLとしてビルドするためのソースファイルを指定
add_library(UserEngineCommon SHARED ${cppfiles})
message("==userenginecommon cmake start ==")
message(${PROJECT_SOURCE_DIR}/../ThirdPartyLibrary/lib)
message(${PROJECT_SOURCE_DIR}/include)

target_include_directories(
    UserEngineCommon PRIVATE
    ${PROJECT_SOURCE_DIR}/../ThirdPartyLibrary/lib
    ${PROJECT_SOURCE_DIR}/../UserEngineCommon/include
)
message("==userenginecommon cmake end ==")

# 実行可能ファイルのインストール先を指定
install(TARGETS UserEngineCommon
    LIBRARY DESTINATION)