cmake_minimum_required(VERSION 3.1)
project(ExeProject CXX)

set(CMAKE_CXX_STANDARD 17)
add_executable(ExeProject ./src/main.cpp)

message(${CMAKE_BINARY_DIR})
add_subdirectory(./../Core
    ${CMAKE_BINARY_DIR}/Core)

add_subdirectory(
    D:/tmp/Densannkenn/YoujinProject/Yougine/Engine/UserEngineCommon
    ${CMAKE_BINARY_DIR}/UserEngineCommon
)
target_include_directories(
    ExeProject PRIVATE
    ${PROJECT_SOURCE_DIR}/../Core/lib
    ${PROJECT_SOURCE_DIR}/../Core/lib/glew/include
    ${PROJECT_SOURCE_DIR}/../Core/lib/glfw/include
    ${PROJECT_SOURCE_DIR}/../Core/src/yougine
    ${PROJECT_SOURCE_DIR}/../ThirdPartyLibrary/lib
    ${PROJECT_SOURCE_DIR}/../UserEngineCommon/include
)

target_link_directories(
    ExeProject PRIVATE
    ${PROJECT_SOURCE_DIR}/../Core/lib/glew/lib
    ${PROJECT_SOURCE_DIR}/../Core/lib/glfw/lib
    ${PROJECT_SOURCE_DIR}/../x64/Debug
)
message("${linkDir}")


target_link_libraries(ExeProject YouginLib opengl32 libglew32d glfw3 UserEngineCommon)

# 実行可能ファイルのインストール先を指定
install(TARGETS ExeProject
    RUNTIME DESTINATION)
