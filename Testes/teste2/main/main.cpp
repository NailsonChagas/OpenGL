//Criando uma janela

#include <iostream>
#include <cassert>
#include <GLFW/glfw3.h>

int main(){
    const int largura = 800, altura = 600;

    //Inicia a GLFW
    assert(glfwInit());

    //Cria a janela
    GLFWwindow *janela;
    janela = glfwCreateWindow(largura, altura, "Teste 2", nullptr, nullptr); // -->Criar uma janela de 800x600 pixels de 3 bytes (480000 pixels * 3 = 1.4 MB de RAM)
    assert(janela);

    //Loop de Eventos
    while (!glfwWindowShouldClose(janela))
    {
        //processa todos os eventos na fila de eventos do GLFW (teclado, mause, gamepad)
        glfwPollEvents();

        //Envia o conteudo do framebuffer da janela para ser desenhado na tela
        glfwSwapBuffers(janela); //pega o 1.4 MB de dados (da memória RAM) da janela e envia (para a memória de vídeo) para ser desenhado na tela do computador 
    }
    

    //Encerra a GLFW
    glfwTerminate();

    return 0;
}