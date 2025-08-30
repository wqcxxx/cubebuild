cmake_minimum_required(VERSION 3.15...4.0)

project(cubebuild VERSION 0.1 LANGUAGES CXX C)

find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

list(APPEND SOURCES include/glad/glad/src/glad.c)

set(SOURCES src/main.cpp
            src/cubebuild/Shader.cpp
            src/cubebuild/Camera.cpp
            src/cubebuild/World/Block.cpp
            src/cubebuild/World/Chunk.cpp
            src/cubebuild/World/World.cpp
            src/cubebuild/Utility/PerlinNoise.cpp
            src/cubebuild/Utility/Generator.cpp
            src/cubebuild/Texture.cpp
            src/cubebuild/Skybox.cpp
)

set(HEADERS third_party/stb_image/include
            include/cubebuild/Shader
            include/cubebuild/Camera
            include/cubebuild/Block
            include/cubebuild/Chunk
            include/cubebuild/Utility
            include/cubebuild/World
            include/cubebuild/Texture
            include/cubebuild/Skybox
)

add_library(imgui STATIC 
        third_party/imgui/imgui.cpp
        third_party/imgui/imgui_draw.cpp
        third_party/imgui/imgui_tables.cpp
        third_party/imgui/imgui_widgets.cpp
        third_party/imgui/imgui_impl_glfw.cpp
        third_party/imgui/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC
        third_party/imgui
)   

add_library(glad third_party/glad/include/glad/glad.h third_party/glad/src/glad.c)
target_include_directories(glad PUBLIC third_party/glad/include)

add_executable(${PROJECT_NAME} ${SOURCES})
include_directories(${PROJECT_NAME} ${HEADERS})
target_include_directories(${PROJECT_NAME} PRIVATE ${HEADERS})

target_link_libraries(${PROJECT_NAME} glad
                                      OpenGL::GL
                                      glfw
                                      glm::glm
                                      imgui
)


