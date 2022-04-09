#include "camera.h"

Camera::Camera(){}

Camera::Camera(glm::vec3 start_position, glm::vec3 start_up, GLfloat start_yaw, GLfloat start_pitch, GLfloat start_moveSpeed, GLfloat start_turnSpeed){
    position = start_position;
    world_up = start_up;
    yaw = start_yaw;
    pitch = start_pitch;
    front = glm::vec3(0.0f, 0.0f, -1.0f);

    move_speed = start_moveSpeed;
    turn_speed = start_turnSpeed;

    update();
}

void Camera::key_control(bool *keys, GLfloat deltaTime){
    
    GLfloat velocity = move_speed * deltaTime;

    if(keys[GLFW_KEY_W]){
        position += front * velocity;
    }
    if(keys[GLFW_KEY_S]){
        position -= front * velocity;
    }
    if(keys[GLFW_KEY_A]){
        position -= right * velocity;
    }
    if(keys[GLFW_KEY_D]){
        position += right * velocity;
    }
}

void Camera::mouse_control(GLfloat x_change, GLfloat y_change){
    x_change *= turn_speed;
    y_change *= turn_speed;

    yaw += x_change;
    pitch += y_change;

    if(pitch > 89.0f){
        pitch = 89.0f;
    }

    if(pitch < -89.0f){
        pitch = -89.0f;
    }

    update();
}

glm::mat4 Camera::calculate_view_matrix(){
    return glm::lookAt(position, position + front, up);
}

void Camera::update(){
    //calculado front
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front); //transformando em vetor unitario

    right = glm::normalize(glm::cross(front, world_up));
    up = glm::normalize(glm::cross(right, front));
}

Camera::~Camera(){

}