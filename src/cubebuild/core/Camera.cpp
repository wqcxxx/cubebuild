 #include <Camera.h>

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) 
    : front(glm::vec3(0.0f, 0.0f, -1.0f)), 
      movement_speed(SPEED), 
      mouse_sensitivity(SENSITIVITY), 
      zoom(ZOOM) 
{
    this->position = position;
    world_up = up;
    this->yaw = yaw;
    this->pitch = pitch;
    update_camera_vectors();
}

Camera::Camera(float pos_x, float pos_y, float pos_z, 
               float up_x, float up_y, float up_z, 
               float yaw, float pitch) 
               : front(glm::vec3(0.0f, 0.0f, -1.0f)), 
                movement_speed(SPEED), 
                mouse_sensitivity(SENSITIVITY), 
                zoom(ZOOM) 
{
    position = glm::vec3(pos_x, pos_y, pos_z);
    world_up = glm::vec3(up_x, up_y, up_z);
    this->yaw = yaw;
    this->pitch = pitch;
    update_camera_vectors();
}

glm::mat4 Camera::get_view_matrix()
{
    return glm::lookAt(position, position + front, up);
}

void Camera::process_keyboard(Camera_Movement direction, float delta_time)
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
}

void Camera::process_mouse_movement(float xoffset, float yoffset, GLboolean constrain_pitch)
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

void Camera::process_mouse_scroll(float yoffset)
{
    zoom = glm::clamp(zoom - yoffset, 1.0f, 90.0f);
}

glm::vec3 Camera::get_position()
{
    return glm::vec3(this->position);
}

void Camera::update_camera_vectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->front = glm::normalize(front);

    right = glm::normalize(glm::cross(this->front, this->world_up));  
    up = glm::normalize(glm::cross(this->right, this->front));
}