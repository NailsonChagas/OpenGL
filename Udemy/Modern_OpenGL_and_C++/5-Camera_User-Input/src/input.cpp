#include "input.h"

Input::Input(GLFWwindow *window){
    mainWindow = window;
    mouse_first_move = true;
    last_x = 0; 
    last_y = 0; 
    current_x = 0; 
    current_y = 0; 
    change_x = 0; 
    change_y = 0;

    for(size_t i=0; i < 1024; i++){
        keys[i] = false;
    }

    glfwSetWindowUserPointer(mainWindow, this);
}

Input::~Input(){}

void Input::handle_keys(GLFWwindow *window, int key, int code, int action, int mode){
    Input* window_input = static_cast<Input*>(glfwGetWindowUserPointer(window));

    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if(key >= 0 && key < 1024){
        if(action == GLFW_PRESS){
            window_input->keys[key] = true;
            //std::cout << "Pressed: " << key << std::endl;
        }
        else if(action == GLFW_RELEASE){
            window_input->keys[key] = false;
            //std::cout << "Released: " << key << std::endl;
        }
    }
}

void Input::handle_mouse_pos(GLFWwindow *window, double x_pos, double y_pos){
    Input* window_input = static_cast<Input*>(glfwGetWindowUserPointer(window));

    window_input->current_x = x_pos;
    window_input->current_y = y_pos;

    if(window_input->mouse_first_move){
        window_input->last_x = x_pos;
        window_input->last_y = y_pos;
        window_input->mouse_first_move = false;
    }

    window_input->change_x = x_pos - window_input->last_x; 
    window_input->change_y = window_input->last_y - y_pos; 

    window_input->last_x = x_pos;
    window_input->last_y = y_pos;

    //std::cout << "x: " << window_input->change_x << "  \\ y: " << window_input->change_y << "  \\ last_x: "<< window_input->last_x << "  \\ last_y: "<< window_input->last_y <<std::endl;
}

void Input::reset_change_mouse_pos(GLFWwindow *window){
    Input* window_input = static_cast<Input*>(glfwGetWindowUserPointer(window));

    window_input->change_x = 0;
    window_input->change_y = 0;
    window_input->mouse_first_move = true;
}

void Input::create_callbacks(bool hidden_cursor){
    glfwSetKeyCallback(mainWindow, handle_keys);
    glfwSetCursorPosCallback(mainWindow, handle_mouse_pos);

    if(hidden_cursor){
        glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}