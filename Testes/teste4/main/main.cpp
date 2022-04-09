//Iniciar o OpenGL

#include <iostream>
#include <assert.h>

#include <GL/glew.h> //carrega todas funções do OpenGL
#include <GLFW/glfw3.h>


int main(){
    const int altura = 600, largura = 800;
    GLFWwindow *janela = nullptr;
    GLenum err;

    assert(glfwInit() == GLFW_TRUE);

    janela = glfwCreateWindow(largura, altura, "Teste 4", nullptr, nullptr);
    glfwMakeContextCurrent(janela);

    //Após iniciar o contexto do openGL iniciar o glew
    err = glewInit(); //recebe qualquer notificação sobre a inicialização

    //Verificar a versão do OpenGL
    GLint GLMajorVersion = 0;
    glGetIntegerv(GL_MAJOR_VERSION, &GLMajorVersion);

    if(err != GLEW_OK){
        std::cout << "Error: " << glewGetErrorString(err) << std::endl;
    }
    else{
        //verificar versão openGl
        std::cout << "Using GLEW: " << glewGetString(GLEW_VERSION) << " OpenGL: "<< GLMajorVersion << std::endl;
    }

    //Definir cor de fundo
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

    while (!glfwWindowShouldClose(janela))
    {
        //glClear: limpar o framebuffer. GL_COLOR_BUFFER_BIT vai limpar o buffer prencendo com a cor definida no glClearColor
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();
        glfwSwapBuffers(janela);
    }
    
    glfwTerminate();
}