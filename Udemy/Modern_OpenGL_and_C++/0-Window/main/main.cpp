#include "window.h"

/*
Esse é um exemplo de criação de uma janela com OpenGL
*/

// Window dimensions
const GLint WIDTH = 800, HEIGHT = 600;

int main()
{
	// Initialise GLFW
	if(!init_glfw(3,3)){return -1;}//ponto de saida 1

	GLFWwindow *mainWindow = create_window(WIDTH,HEIGHT, "Window - Exemplo", NULL, NULL);
	if(!mainWindow){return -2;}//ponto de saida 2

	//	Initialise GLEW
	if(!init_glew(mainWindow)){return -3;}//ponto de saida 3

	// Loop until window closed
	while (!glfwWindowShouldClose(mainWindow))
	{
		// Get + Handle user input events
		glfwPollEvents();

		// Clear window
		glClearColor(0.0f, 0.3f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(mainWindow);
	}

	glfwDestroyWindow(mainWindow);
	glfwTerminate();

	return 0;
}