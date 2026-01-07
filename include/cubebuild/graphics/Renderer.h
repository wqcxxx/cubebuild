#pragma once 

#include <GLFW/glfw3.h>

class Renderer 
{
    public: 
        void initialize_glfw(const int screen_width, const int screen_height, const char* name);
        void initialize_glad();
        void setup_callbacks();
        void initialize_imgui();

    protected: 

    private: 
        const int m_screen_width, m_screen_height;
        GLFWwindow* m_window;

};