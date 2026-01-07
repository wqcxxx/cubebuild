#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class GLContextManager
{
    public:
        GLContextManager();
        ~GLContextManager();

        GLContextManager(const GLContextManager&) = delete;
        GLContextManager(GLContextManager&&) = delete;
        GLContextManager& operator=(const GLContextManager&) = delete;
        GLContextManager& operator=(GLContextManager&&) = delete;

        void glad_init();
        void enable_depth_test(bool enable = true);
        void clear_color(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
        void gl_clear();
};