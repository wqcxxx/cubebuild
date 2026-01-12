#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Window.h>

enum Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Player {
    public:
        Player(glm::vec3 position);
        //~Player( );

        void setup_callbacks(GLFWwindow* window);

        void update(Window& win);
        void handle_movement(GLFWwindow* window, float delta_time);
        void process_keyboard(Movement direction, float delta_time);

        void process_mouse_movement(float xoffset, float yoffset, GLboolean constrain_pitch = true);
        void process_mouse_scroll(float yoffset);

        float get_zoom();
        glm::vec3 get_player_position();
        glm::mat4 get_view_matrix();
        float get_speed();

        void set_speed(float speed);
        void set_position(glm::vec3 position);        
        void set_camera_variables(float last_x, float last_y, bool first_movement); 

    private:
        float last_x = 0.0f;
        float last_y = 0.0f;
        bool first_movement = true;

        glm::vec3 front;
        glm::vec3 position;
        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 world_up;

        float yaw;
        float pitch;
        float movement_speed;
        float mouse_sensitivity;
        float zoom;

        void update_camera_vectors();

        void handle_mouse_movement(double x_pos_in, double y_pos_in);
        void handle_scroll_mouse(double x_offset, double y_offset);
};