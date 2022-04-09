#include <iostream>
#include "window.h"

bool init_glfw(int major_version, int minor_version){
    if(!glfwInit()){
        std::cout << "GLFW initialisation FAILED " << std::endl;
        glfwTerminate();
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_version);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_version);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    std::cout << "GLFW initialisation SUCCESSFUL" << std::endl;
    return true;
}

bool init_glew(GLFWwindow *window_for_context){
    /*
    inicia o glew e set viewport
    */
    glfwMakeContextCurrent(window_for_context);
    glewExperimental = GL_TRUE;

    if(glewInit() != GLEW_OK){
        std::cout << "GLEW initialisation FAILED" << std::endl;
        glfwDestroyWindow(window_for_context);
        glfwTerminate();
        return false;
    }

    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(window_for_context, &bufferWidth, &bufferHeight);
    glViewport(0, 0, bufferWidth, bufferHeight);
    glEnable(GL_DEPTH_TEST);
    std::cout << "GLEW initialisation SUCCESSFUL" << std::endl;
    return true;
}

GLFWwindow *create_window(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share){
    GLFWwindow *window = glfwCreateWindow(width, height, title, monitor, share);
    if(!window){
        std::cout << "GLFWwindow creation FAILED" << std::endl;
        glfwTerminate();
        return NULL;
    }
    std::cout << "GLFWwindow creation SUCCESSFUL" << std::endl;
    return window;
}

