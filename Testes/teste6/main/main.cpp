//Primeiro trinagulo desenhado
//Definindo um triangulo
//toda API gráfica tabalha com coordenas normalizadas assim a definição da gemometria fica independente da tela
//eixo x: -1 até 1  / eixo y: -1 até 1 / eixo z: -1 até 1

#include <iostream>
#include <array> //para usar array em C++
#include <assert.h>
#include <GL/glew.h> //carrega todas funções do OpenGL
#include <GLFW/glfw3.h> //carrega as funções da Graphics Library Framework
#include <glm/glm.hpp> // carrega as funções da OpenGL Mathematics (calculo com vetores e pontos) 

int main(){
    const int largura = 800, altura = 600;
    GLFWwindow *janela = nullptr;
    
    assert(glfwInit() == GLFW_TRUE); //inicia a GLFW

    janela = glfwCreateWindow(largura, altura, "Teste 6", nullptr, nullptr); //Cria a janela (cada pixel 3bytes)
    glfwMakeContextCurrent(janela); //inicia o contexto OpenGL na janela

    glewInit(); //inicia a GLEW

    /*Pegando a versão e dados sobre o OpenGL*/
    GLint GLMajorVersion = 0, GLMinorVersion = 0;
    glGetIntegerv(GL_MAJOR_VERSION, &GLMajorVersion);
    glGetIntegerv(GL_MINOR_VERSION, &GLMinorVersion);
    std::cout << "OpenGL version: " << GLMajorVersion << "." << GLMinorVersion << std::endl;

    /*Pegandos dados usando getString*/
    std::cout << "OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


    //Definindo um triangulo em coordenadas normalizadas
    std::array<glm::vec3, 3> Triangle = { //cria um vetor de tamanho 3 de tipo glm::bvec3 chamado de Triangle
        glm::vec3{-1.0f, -1.0f, 0.0f},
        glm::vec3{1.0f, -1.0f, 0.0f},
        glm::vec3{0.0f, 1.0f, 0.0f}
    };
    
    //Copiando os vertices do triangulo para memória da GPU
    GLuint VertexBuffer; //identifcador da memória que vamos criar para poder copiar os vértices

    //Pedir para o OpenGL gerar o identificador do VertexBuffer
    glGenBuffers(1, &VertexBuffer);

    //Ativar o VertexBuffer como sendo o buffer para onde vamos copiar os vertices do triangulo
    glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer); 

    //copiar vértices para memória de vídeo
    glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle), Triangle.data(), GL_STATIC_DRAW);

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f); //define a cor de fundo

    while(!glfwWindowShouldClose(janela)){
        //glClear: limpa o framebuffer. 
        //GL_COLOR_BUFFER_BIT: vai limpar o buffer prenchendo com a cor do glClearColor
        glClear(GL_COLOR_BUFFER_BIT);

        //Habilita vertex array na posição 0
        glEnableVertexAttribArray(0);

        //Diz que o VertexBuffer vai ser o buffer ativo no momento
        glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);

        //Informa ao openGL onde dentro do vertexBuffer os vértices estão
        //No caso o array Triangles é contiguo em memóriam logo basta apenas dizer os vértices necessários para se desenhar o triangulo
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr); //nullptr usa o ponteiro q já esta na memória

        //Diz para o openGL  desenhar o triangulo com os dados armazenados no vertex buffer
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //Reverter o estado criado
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDisableVertexAttribArray(0);

        glfwPollEvents(); //processa todos os eventos na fila de eventos do GLFW (teclado, mause, gamepad)
        glfwSwapBuffers(janela); //Envia o conteudo do framebuffer da janela para ser desenhado na tela
    }

    //Desalocar o VertexBuffer
    glDeleteBuffers(1, &VertexBuffer);

    glfwTerminate();

    return 0;
}