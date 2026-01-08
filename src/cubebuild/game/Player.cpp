#include "Player.h"

Player::Player() {}

void Player::update(Window& win) 
{
    current_frame = static_cast<float>(glfwGetTime());
    delta_time = current_frame - last_frame;
    last_frame = current_frame;
}

void Player::set_camera(Window& window)
{
    window.get_camera().position = glm::vec3(16.0f, 32.0f, 16.0f);
    window.set_camera_variables(last_x, last_y, first_movement);
}

void Player::handle_movement(Window& win)
{
    GLFWwindow* window = win.get_window();
    Camera& camera = win.get_camera();

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwWindowShouldClose(window);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.process_keyboard(FORWARD, delta_time);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.process_keyboard(BACKWARD, delta_time);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.process_keyboard(LEFT, delta_time);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.process_keyboard(RIGHT, delta_time);
}

Camera& Player::get_camera(Window& window)
{
    return window.get_camera();
}