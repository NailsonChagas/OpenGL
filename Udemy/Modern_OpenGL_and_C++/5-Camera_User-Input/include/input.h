#pragma once

#include <GLFW/glfw3.h>
#include <iostream>

class Input{
    public:
        Input(GLFWwindow *window);
        ~Input();

        void create_callbacks(bool hidden_cursor);

        bool *get_keys(){return keys;}
        bool get_specific_key(int key){return keys[key];}
        int get_current_pos_X_mouse(){return current_x;}
        int get_change_pos_X_mouse(){return change_x;}
        int get_current_pos_Y_mouse(){return current_y;}
        int get_change_pos_Y_mouse(){return change_y;}
        void reset_change_mouse_pos(GLFWwindow *window);

    private:
        GLFWwindow *mainWindow;
        bool keys[1024]; //array ASCII 
        
        GLfloat last_x, last_y, current_x, current_y, change_x, change_y;
        bool mouse_first_move;

        static void handle_keys(GLFWwindow *window, int key, int code, int action, int mode);
        static void handle_mouse_pos(GLFWwindow *window, double x_pos, double y_pos);
};