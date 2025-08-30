#pragma once 

#include <glad/glad.h>
#include <vector>
#include <iostream>

#include <Shader.h>

class Skybox 
{
    public:
        Skybox();
        ~Skybox();

        GLuint load_cubemap();
        void draw(Shader shader, const glm::mat4& view, const glm::mat4& projection);
        
    private:
        GLuint m_textureID, m_VAO, m_VBO;
        
        std::vector<std::string> m_faces = {
            "right.jpg", "left.jpg", "top.jpg", "bottom.jpg", "front.jpg", "back.jpg" //skybox is from LearnOpengl.com
        };

        void setup();
};