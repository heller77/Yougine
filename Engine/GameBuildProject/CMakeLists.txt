cmake_minimum_required(VERSION 3.1)
project(ExeProject CXX)

set(CMAKE_CXX_STANDARD 17)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_subdirectory(./../Core ./../Core/Build)

set(includeDir
    ${PROJECT_SOURCE_DIR}/../Core/lib
    ${PROJECT_SOURCE_DIR}/../Core/lib/glew/include
    ${PROJECT_SOURCE_DIR}/../Core/lib/glfw/include
    ${PROJECT_SOURCE_DIR}/../Core/src/yougine
)

include_directories("${includeDir}")
set(linkDir
    ${PROJECT_SOURCE_DIR}/../Core/lib/glew/lib
    ${PROJECT_SOURCE_DIR}/../Core/lib/glfw/lib
)

link_directories("${linkDir}")

# message(${includeDir})
add_executable(ExeProject ./src/main.cpp)
target_link_libraries(ExeProject YouginLib)
target_link_libraries(ExeProject opengl32 libglew32d glfw3)