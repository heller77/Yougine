# cmakeのバージョン
cmake_minimum_required(VERSION 3.1)

# プロジェクト名指定
project(YouginBuild CXX)

# srcフォルダー以下のcppファイル一覧をcppfilesという変数に格納
file(GLOB_RECURSE cppfiles RELATIVE ${PROJECT_SOURCE_DIR} ./lib/*.cpp ./src/*.cpp)
#list(FILTER cppfiles EXCLUDE REGEX ".*main.cpp$")
list(LENGTH cppfiles list_length)

message(${cppfiles})

set(CMAKE_CXX_STANDARD 17)

set(includeDir
    ${PROJECT_SOURCE_DIR}/lib
    ${PROJECT_SOURCE_DIR}/lib/glew/include
    ${PROJECT_SOURCE_DIR}/lib/glfw/include
)
set(linkDir
    ${PROJECT_SOURCE_DIR}/lib/glew/lib
    ${PROJECT_SOURCE_DIR}/lib/glfw/lib
)

# target_include_directories(${PROJECT_SOURCE_DIR}../../../lib/)
include_directories("${includeDir}")
link_directories("${linkDir}")

add_compile_definitions(IMGUI_IMPL_OPENGL_LOADER_GLEW)
add_compile_definitions(GLEW_STATIC)
# message("${includeDir}")

# target_include_directories(${PROJECT_SOURCE_DIR}../../../lib/glfw/include)
get_directory_property(INCLUDE_PATH INCLUDE_DIRECTORIES)
#message(${CMAKE_BINARY_DIR})

# exeでビルドすると指定
add_executable(a.out ${cppfiles})
target_link_libraries(a.out opengl32 libglew32d glfw3)

file(COPY ${PROJECT_SOURCE_DIR}/Resource DESTINATION ${CMAKE_BINARY_DIR}/Debug)
