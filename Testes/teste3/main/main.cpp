//Pipeline de Renderização
#include <iostream>
#include <cassert>
#include <GLFW/glfw3.h>

//Pipeline (tubulação) = sequencia de passos que devem ser tomados para realizar uma tarefa
//Dividir em etapas aumenta a "vazão"

//Pipeline de Renderização = processo pelo qual se obtem um produto final através de um processamento qualquer
//Computação gráfica = converter um modelo 3D para uma imagem estática 2D

//Pipeline de Renderização: aplicação -> geometria -> projeção -> rasterização -> tela
//-aplicação: um programa desenhando algo na tela (modelando alguma geometria)
//-geometria: modelos 3D e Texturas 
//-projeção: dividida em dois, ortografica (linhas paralelas continuam paralelas) e perspectiva(ponto de perspectiva em que as linhas paralelas no modelo original vão convergir nesse ponto), 
//-rasterização: identificar que pedaços da tela (pixels) a geometira ocupa
//-tela: a imagem desenhada em um plano 2D (tela)

//Fluxo de dados: CPU(geometria, textura, shaders e comandos) -> GPU -> Tela

//Pipeline de renderização do openGL
//vertex Specification-> vertex shader-> tessellation-> geometry shader-> vertex post-processing-> primitive assembly-> rasterization-> fragment shader ->per-sample operations

int main(){
    const int largura = 800, altura = 600;
    GLFWwindow *janela;

    assert(glfwInit());

    janela = glfwCreateWindow(largura, altura, "Teste 3", nullptr, nullptr);
    assert(janela);

    while (!glfwWindowShouldClose(janela))
    {
        glfwPollEvents();
        glfwSwapBuffers(janela);
    }
    
    glfwTerminate();

    return 0;
}