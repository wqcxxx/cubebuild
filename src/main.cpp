#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <Shader.h>
#include <Block.h>
#include <BlockType.h>
#include <Camera.h>
#include <Chunk.h>
#include <Generator.h>
//#include <World.h> //needs to be done
#include <Texture.h>
#include <Skybox.h>
#include <Player.h>

#include <Window.h>
#include <UIManager.h>
#include <GLContextManager.h>

#include <iostream>
#include <vector>
#include <filesystem>

const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

void process_input(Window& win);

int main()
{
    Player player;
    Window window;
    window.initialize_glfw();
    window.create_window(SCR_WIDTH, SCR_HEIGHT, "cubebuild");
    player.set_camera(window);
    window.setup_callbacks();
    window.set_swap_internal();
    window.set_input_mode();

    GLContextManager gl_context_manager;

    UIManager ui_manager;
    ui_manager.setup_imgui_context();
    ui_manager.set_dark_style();
    ui_manager.setup_scaling();
    ui_manager.glfw_opengl_init(window, "#version 330 core");

    std::filesystem::path vertex_shader_path = std::filesystem::current_path().parent_path() / "resources/shaders/vertex_shader.glsl";
    std::filesystem::path fragment_shader_path = std::filesystem::current_path().parent_path() / "resources/shaders/fragment_shader.glsl";
    std::filesystem::path skybox_vertex_path = std::filesystem::current_path().parent_path() / "resources/shaders/skybox_vertex.glsl";
    std::filesystem::path skybox_fragment_path = std::filesystem::current_path().parent_path() / "resources/shaders/skybox_fragment.glsl";

    std::filesystem::path texture_path = std::filesystem::current_path().parent_path() / "resources/textures/sprites.png";

    Shader shader(vertex_shader_path.string().c_str(), fragment_shader_path.string().c_str());
    Texture texture_sprites(texture_path.string().c_str(), 2);
    Skybox skybox; 
    Shader skybox_shader(skybox_vertex_path.string().c_str(), skybox_fragment_path.string().c_str());

    Generator generator(213654);
    Chunk chunk(0, 0);

    generator.generate_terrain(chunk, texture_sprites);
    
    gl_context_manager.enable_depth_test(true);

    shader.use();
    shader.set_int("texture1", 0);

    while (!window.should_close())
    {
        window.poll_events();

        player.update(window);

        ui_manager.imgui_glfw_opengl_new_frame();
        ui_manager.new_frame();

        texture_sprites.bind(GL_TEXTURE0);

        player.handle_movement(window);

        gl_context_manager.clear_color(0.05f, 0.05f, 0.05f, 1.0f);
        gl_context_manager.gl_clear();

        glm::mat4 view       = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        Camera& camera = player.get_camera(window);
        projection = glm::perspective(glm::radians(camera.zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        view       = camera.get_view_matrix(); 

        shader.use();
        shader.set_mat4("view", view);
        shader.set_mat4("projection", projection);
        
        chunk.render(shader);
        skybox.draw(skybox_shader, view, projection);

        ui_manager.render();
        window.swap_buffers();
    }
    return 0;
}


