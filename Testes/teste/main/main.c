#include <GLFW/glfw3.h>

int main(){
    GLFWwindow *janela;

    glfwInit();

    janela = glfwCreateWindow(800,600,"teste", NULL, NULL);
    glfwMakeContextCurrent(janela);

    while (!glfwWindowShouldClose(janela))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(janela);
        glfwPollEvents();
    }
    
    glfwTerminate();

    return 0;
}