#include "Player.h"

Player::Player(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f)) 
    : front(glm::vec3(0.0f, 0.0f, -1.0f)), 
      movement_speed(5.0f), 
      mouse_sensitivity(0.1f), 
      zoom(45.0f),
      position(position),
      yaw(-90.0f),
      world_up(glm::vec3(0.0f, 1.0f, 0.0f)),
      pitch(0.0f)
{
    update_camera_vectors();
}

void Player::setup_callbacks(GLFWwindow* window)
{
    glfwSetWindowUserPointer(window, this);

    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y) 
    {
        Player* player = static_cast<Player*>(glfwGetWindowUserPointer(window));
        if (player) player->handle_mouse_movement(x, y);
    });

    glfwSetScrollCallback(window, [](GLFWwindow* window, double x_offset, double y_offset)
    {
        Player* player = static_cast<Player*>(glfwGetWindowUserPointer(window));
        if (player) player->handle_scroll_mouse(x_offset, y_offset);
    });
}

void Player::update(Window& win) 
{
}

void Player::handle_movement(GLFWwindow* window, float delta_time)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwWindowShouldClose(window);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) process_keyboard(FORWARD, delta_time);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) process_keyboard(BACKWARD, delta_time);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) process_keyboard(LEFT, delta_time);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) process_keyboard(RIGHT, delta_time);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) process_keyboard(DOWN, delta_time);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) process_keyboard(UP, delta_time);
}

void Player::process_keyboard(Movement direction, float delta_time)
{
    float velocity = movement_speed * delta_time;
    
    if (direction == FORWARD)
        position += front * velocity;
    if (direction == BACKWARD)
        position -= front * velocity;
    if (direction == LEFT)
        position -= right * velocity;
    if (direction == RIGHT)
        position += right * velocity;
    if (direction == UP)
        position += world_up * velocity;
    if (direction == DOWN)
        position -= world_up * velocity;
}

void Player::set_speed(float speed)
{
    this->movement_speed = speed;
}

void Player::set_position(glm::vec3 position)
{
    this->position = position;
}

glm::vec3 Player::get_player_position()
{
    return position;
}

glm::mat4 Player::get_view_matrix()
{
    return glm::lookAt(position, position + front, up);
}

float Player::get_zoom()
{
    return zoom;
}

float Player::get_speed()
{
    return movement_speed;
}

void Player::process_mouse_movement(float xoffset, float yoffset, GLboolean constrain_pitch)
{
    xoffset *= mouse_sensitivity;
    yoffset *= mouse_sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (constrain_pitch)
    {
        pitch = glm::clamp(pitch, -89.0f, 89.0f);
    }

    update_camera_vectors();
}

void Player::process_mouse_scroll(float yoffset)
{
    zoom = glm::clamp(zoom - yoffset, 1.0f, 90.0f);
}

void Player::handle_mouse_movement(double x_pos_in, double y_pos_in)
{
    float x_pos = static_cast<float>(x_pos_in);
    float y_pos = static_cast<float>(y_pos_in);

    if (first_movement)
    {
        last_x = x_pos;
        last_y = y_pos;
        first_movement = false;
    }

    float x_offset = x_pos - last_x;
    float y_offset = last_y - y_pos;

    last_x = x_pos;        
    last_y = y_pos;

    process_mouse_movement(x_offset, y_offset);
}

void Player::handle_scroll_mouse(double x_offset, double y_offset)
{
    process_mouse_scroll(static_cast<float>(y_offset));
}

void Player::set_camera_variables(float last_x, float last_y, bool first_movement) 
{
    this->last_x = last_x;
    this->last_y = last_y;
    this->first_movement = first_movement;
} 

void Player::update_camera_vectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->front = glm::normalize(front);

    right = glm::normalize(glm::cross(this->front, this->world_up));  
    up = glm::normalize(glm::cross(this->right, this->front));
}