#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>

class Camera{
    public:
        Camera();
        Camera(glm::vec3 start_position, glm::vec3 start_up, GLfloat start_yaw, GLfloat start_pitch, GLfloat start_moveSpeed, GLfloat start_turnSpeed);        
        
        void key_control(bool *keys, GLfloat deltaTime);
        void mouse_control(GLfloat x_change, GLfloat y_change);
        glm::mat4 calculate_view_matrix();

        ~Camera();

    private:
        glm::vec3 position; //posição da camera
        glm::vec3 front; //direção
        glm::vec3 up; //up da camera
        glm::vec3 right;
        glm::vec3 world_up; //up do mundo

        GLfloat yaw;
        GLfloat pitch;

        GLfloat move_speed;
        GLfloat turn_speed;

        void update();
};