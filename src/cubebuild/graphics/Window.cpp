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
    glfwSetCursorPosCallback(m_window, mouse_callback);
    glfwSetScrollCallback(m_window, scroll_callback);
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (win) win->handle_framebuffer_size(width, height);
}

void Window::mouse_callback(GLFWwindow *window, double x_pos_in, double y_pos_in)
{
    Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (win) win->handle_mouse_movement(x_pos_in, y_pos_in);
}

void Window::scroll_callback(GLFWwindow *window, double x_offset, double y_offset)
{
    Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (win) win->handle_scroll_mouse(x_offset, y_offset);
}

void Window::handle_framebuffer_size(int width, int height)
{
    glViewport(0, 0, width, height);
}

void Window::handle_mouse_movement(double x_pos_in, double y_pos_in)
{
    float x_pos = static_cast<float>(x_pos_in);
    float y_pos = static_cast<float>(y_pos_in);

    if (m_first_movement)
    {
        m_last_x = x_pos;
        m_last_y = y_pos;
        m_first_movement = false;
    }

    float x_offset = x_pos - m_last_x;
    float y_offset = m_last_y - y_pos;

    m_last_x = x_pos;
    m_last_y = y_pos;

    m_camera.process_mouse_movement(x_offset, y_offset);
}

void Window::handle_scroll_mouse(double x_offset, double y_offset)
{
    m_camera.process_mouse_scroll(static_cast<float>(y_offset));
}

void Window::set_camera(const Camera& camera) noexcept
{
    m_camera = camera;
}

void Window::set_camera_variables(float last_x, float last_y, bool first_movement) noexcept
{
    m_last_x = last_x;
    m_last_y = last_y;
    m_first_movement = first_movement;
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

Camera& Window::get_camera() noexcept
{
    return m_camera;
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
