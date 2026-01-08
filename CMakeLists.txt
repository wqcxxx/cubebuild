# cmake_minimum_required(VERSION 3.15...4.0)

# project(cubebuild VERSION 0.1 LANGUAGES CXX C)

# find_package(glfw3 CONFIG REQUIRED)
# find_package(OpenGL REQUIRED)
# find_package(glm REQUIRED)

# set(SOURCES src/main.cpp
#             src/cubebuild/core/Camera.cpp 
#             src/cubebuild/core/FrustumCulling.cpp 
#             src/cubebuild/core/Generator.cpp 
#             src/cubebuild/core/PerlinNoise.cpp 
#             src/cubebuild/game/Game.cpp 
#             src/cubebuild/graphics/Shader.cpp 
#             src/cubebuild/graphics/Skybox.cpp 
#             src/cubebuild/graphics/Texture.cpp 
#             src/cubebuild/world/Block.cpp 
#             src/cubebuild/world/Chunk.cpp 
#             src/cubebuild/world/World.cpp
#             src/cubebuild/graphics/UIManager.cpp 
#             src/cubebuild/graphics/Renderer.cpp
#             src/cubebuild/graphics/Window.cpp
#             src/cubebuild/core/GLContextManager.cpp
# )

# set(HEADERS third_party/stb_image/include
#             include/cubebuild/core 
#             include/cubebuild/game 
#             include/cubebuild/graphics 
#             include/cubebuild/world 
#             third_party/glad/include
# )

# add_library(glad third_party/glad/include/glad/glad.h third_party/glad/src/glad.c)
# target_include_directories(glad PUBLIC third_party/glad/include)

# find_path(GLFW_INCLUDE_DIR GLFW/glfw3.h 
#     PATHS 
#         "C:/vcpkg/installed/x64-windows/include"
#         "$ENV{VCPKG_ROOT}/installed/x64-windows/include"
#     REQUIRED
# )
# message(STATUS "GLFW include directory: ${GLFW_INCLUDE_DIR}")

# add_library(imgui STATIC 
#         third_party/imgui/imgui.cpp
#         third_party/imgui/imgui_draw.cpp
#         third_party/imgui/imgui_tables.cpp
#         third_party/imgui/imgui_widgets.cpp
#         third_party/imgui/imgui_impl_glfw.cpp
#         third_party/imgui/imgui_impl_opengl3.cpp
# )

# target_include_directories(imgui PUBLIC
#         third_party/imgui
#         ${GLFW_INCLUDE_DIR}
# )   

# add_executable(${PROJECT_NAME} ${SOURCES})
# include_directories(${PROJECT_NAME} ${HEADERS})

# target_include_directories(${PROJECT_NAME} PRIVATE 
#         ${HEADERS}
#         third_party/stb_image/include
#         third_party/glad/include 
#         third_party/imgui
#         ${GLFW_INCLUDE_DIRS}
# )

# target_link_libraries(${PROJECT_NAME} glad
#                                       OpenGL::GL
#                                       glfw
#                                       imgui 
#                                       glm::glm
# )


cmake_minimum_required(VERSION 3.15...4.0)

project(cubebuild VERSION 0.1 LANGUAGES CXX C)

find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

set(SOURCES src/main.cpp
            src/cubebuild/core/Camera.cpp 
            src/cubebuild/core/FrustumCulling.cpp 
            src/cubebuild/core/Generator.cpp 
            src/cubebuild/core/PerlinNoise.cpp 
            src/cubebuild/game/Game.cpp
            src/cubebuild/game/Player.cpp 
            src/cubebuild/graphics/Shader.cpp 
            src/cubebuild/graphics/Skybox.cpp 
            src/cubebuild/graphics/Texture.cpp 
            src/cubebuild/world/Block.cpp 
            src/cubebuild/world/Chunk.cpp 
            src/cubebuild/world/World.cpp
            src/cubebuild/graphics/UIManager.cpp 
            src/cubebuild/graphics/Renderer.cpp
            src/cubebuild/graphics/Window.cpp
            src/cubebuild/core/GLContextManager.cpp
)

set(HEADERS third_party/stb_image/include
            include/cubebuild/core 
            include/cubebuild/game 
            include/cubebuild/graphics 
            include/cubebuild/world 
            third_party/glad/include
)

add_library(glad third_party/glad/src/glad.c)
target_include_directories(glad PUBLIC third_party/glad/include)

find_package(glfw3 REQUIRED)  

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

target_link_libraries(imgui PUBLIC glfw)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE 
        ${HEADERS}
        third_party/stb_image/include
        third_party/glad/include 
        third_party/imgui
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glad
    glfw      
    OpenGL::GL
    imgui     
    glm::glm
)
