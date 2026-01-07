#pragma once 

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <Camera.h>

#include <iostream>

class Window 
{
    public:
        Window();
        ~Window();

        Window(const Window&) = delete;
        Window(Window&&) = delete;
        Window& operator=(const Window&) = delete;
        Window& operator=(Window&&) = delete;

        void initialize_glfw();
        void create_window(const int screen_width, const int screen_height, const char* title);
        void setup_callbacks();

        void set_camera(const Camera& camera) noexcept;
        void set_camera_variables(float last_x, float last_y, bool first_movement) noexcept; 
        void set_swap_internal() noexcept;
        void set_input_mode() noexcept;

        GLFWwindow* get_window() const noexcept;
        Camera& get_camera() noexcept;

        bool should_close() const noexcept;

        void swap_buffers() noexcept;
        void poll_events() noexcept;

    private:
        GLFWwindow* m_window = nullptr;
        
        Camera m_camera;
        bool m_first_movement = true;
        float m_last_x = 0.0f;
        float m_last_y = 0.0f;

        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        static void mouse_callback(GLFWwindow* m_window, double x_pos_in, double y_pos_in);
        static void scroll_callback(GLFWwindow* m_window, double x_offset, double y_offset);

        void handle_framebuffer_size(int width, int height);
        void handle_mouse_movement(double x_pos_in, double y_pos_in);
        void handle_scroll_mouse(double x_offset, double y_offset);
};