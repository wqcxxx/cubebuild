#pragma once 

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <Window.h>
#include <Player.h>

class UIManager
{
    public:
        UIManager();
        ~UIManager();

        UIManager(const UIManager&) = delete;
        UIManager(UIManager&&) = delete;
        UIManager& operator=(const UIManager&) = delete;
        UIManager& operator=(UIManager&&) = delete;

        void setup_imgui_context();
        void set_dark_style();
        void setup_scaling();
        void glfw_opengl_init(const Window& window, const char* glsl_version);

        void process_input(Window& window);
       
        void imgui_glfw_opengl_new_frame();
        void render();
        void new_frame();
        void end_frame();
       
        void show_player_position(Player& player);
        void show_speed_window(Player& player);

    private:
        bool is_visible_position = false;
        bool is_visible_change_speed = false;

        bool is_r_pressed = false;
        bool is_t_pressed = false;
};