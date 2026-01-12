#include "Window.h"

Window::Window() = default;

Window::~Window()
{
    if (m_window) glfwDestroyWindow(m_window);
}

void Window::initialize_glfw()
{
    glfwInit();
    const char* glsl_version = "#version 330";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
}

void Window::create_window(const int screen_width, const int screen_height, const char* title)
{
    m_window = glfwCreateWindow(screen_width, screen_height, title, nullptr, nullptr);
    if (m_window == nullptr)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window!");
    }

    glfwMakeContextCurrent(m_window);
    glfwSetWindowUserPointer(m_window, this);
}

void Window::setup_callbacks()
{
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (win) win->handle_framebuffer_size(width, height);
}

void Window::handle_framebuffer_size(int width, int height)
{
    glViewport(0, 0, width, height);
}

void Window::set_swap_internal() noexcept
{
    glfwSwapInterval(1);
}

void Window::set_input_mode() noexcept
{
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_CAPTURED);
}

GLFWwindow* Window::get_window() const noexcept
{
    if (m_window) return m_window;
    else return nullptr;
}

bool Window::should_close() const noexcept
{
    return glfwWindowShouldClose(m_window);
}

void Window::swap_buffers() noexcept
{
    if (m_window) glfwSwapBuffers(m_window);
}

void Window::poll_events() noexcept
{
    if (m_window) glfwPollEvents();
}
