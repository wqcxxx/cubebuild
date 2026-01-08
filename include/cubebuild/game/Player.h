#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Camera.h>
#include <Window.h>

class Player {
    public:
        Player();
        //~Player();

        void update(Window& win);
        void handle_movement(Window& win);

        void set_camera(Window& window);
        //void set_position(glm::vec3 position);

        Camera& get_camera(Window& window);

    private:
        float last_x = 1960 / 2;
        float last_y = 1080 / 2;
        bool first_movement = true;

        float delta_time = 0.0f;
        float last_frame = 0.0f;
        float current_frame = 0.0f;

        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
        int velocity = 1.0f;
};