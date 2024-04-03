cmake_minimum_required(VERSION 3.1)
project(ExeProject CXX)

set(CMAKE_CXX_STANDARD 17)
add_executable(ExeProject ./src/main.cpp)

message(${CMAKE_BINARY_DIR})

if(NOT DEFINED ROOTPATH)
    set(ROOTPATH "../")
endif()

message(${ROOTPATH})
message(${ROOTPATH}/Core/src/yougine)

# includeパス
#
target_include_directories(
    ExeProject PRIVATE
    ${ROOTPATH}/ThirdPartyLibrary/lib/glew/include
    ${ROOTPATH}/ThirdPartyLibrary/lib/glfw/include
    ${ROOTPATH}/ThirdPartyLibrary/lib
    ${ROOTPATH}/Core/src/yougine
    ${ROOTPATH}/UserEngineCommon/include
)

# 直下にThirdPartyLibraryフォルダとを配置
target_link_directories(
    ExeProject PRIVATE
    ${ROOTPATH}/ThirdPartyLibrary/lib/glew/lib
    ${ROOTPATH}/ThirdPartyLibrary/lib/glfw/lib
    ${ROOTPATH}
)

# target_link_libraries(ExeProject YouginLib opengl32 libglew32d glfw3 UserEngineCommon)
target_link_libraries(ExeProject Core opengl32 libglew32d glfw3 UserEngineCommon)

# 実行可能ファイルのインストール先を指定
install(TARGETS ExeProject
    RUNTIME DESTINATION)
