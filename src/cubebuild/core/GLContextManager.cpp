#include "GLContextManager.h"

#include <stdexcept>

GLContextManager::GLContextManager()
{
    glad_init();
}

GLContextManager::~GLContextManager() {}

void GLContextManager::glad_init()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("GLAD initialization error!");
    } 
}

void GLContextManager::enable_depth_test(bool enable)
{
    if (enable) glEnable(GL_DEPTH_TEST);
    else glDisable(GL_DEPTH_TEST);
}

void GLContextManager::clear_color(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    glClearColor(r, g, b, a);
}

void GLContextManager::gl_clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

