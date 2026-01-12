#pragma once 

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

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

        void set_swap_internal() noexcept;
        void set_input_mode() noexcept;

        GLFWwindow* get_window() const noexcept;

        bool should_close() const noexcept;

        void swap_buffers() noexcept;
        void poll_events() noexcept;

    private:
        GLFWwindow* m_window = nullptr;

        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        void handle_framebuffer_size(int width, int height);
};