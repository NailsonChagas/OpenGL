#include "window.h"

/*----------- Interpolation ----------- 
- definição: 
	Interpolação é o método de aproximar os valores dos conjuntos discretos.
	Em matemática, denomina-se interpolação o método que permite construir um novo 
	conjunto de dados a partir de um conjunto discreto de dados pontuais previamente 
	conhecidos
- Atributos pertencentes ao vertice são interpolados usando os outros valores da primitiva
- Esses valores são uma estimativa do que o valor deveria ser naquela posição
- Fragment Shader usa esses valores interpolados
- Interpolação ocorre durante a rasterização
- Exemplo clássico: usar coordenadas de posição como valores RGB 
*/

/*----------- Indexed Draws -----------
- usando o mesmo vertice varias vezes para desenhar figuras mais complexas (ex: cubo)
*/

/*----------- Projections -----------
- usado para converter "view-space" para "clip-space"
- conceitos uteis:
	1 - local space = posição pura de cada vertice em relação a origem
	2 - world space = posição do vertice no mundo se a camera é considera a origem
	3 - view space = posição do vertice no mundo, relativo a posição e orientação da camera
	4 - clip space = At the end of each vertex shader run, OpenGL expects the coordinates to be 
	 within a specific range and any coordinate that falls outside this range is clipped. Coordinates that are clipped are discarded, 
	 so the remaining coordinates will end up as fragments visible on your screen. This is also where clip space gets its name from. 
	5 - screen space = imagem no sistema de coordenadas do monitor
- para criar o clip space é definido uma área do não ira ser clipado com uma matriz de projeção.
- tipos de projeção:
	1 - ortografica -> mais usada em 2d
	2 - perspectiva -> mais usada em 3d
*/


//Vertex Shader
static const char *vertex_shader = "				\n\
#version 330										\n\
													\n\
layout (location = 0) in vec3 pos;					\n\
													\n\
out vec4 vertexCol;									\n\
													\n\
uniform mat4 model;									\n\
													\n\
void main(){										\n\
	gl_Position = model * vec4(pos, 1.0);			\n\
	vertexCol = vec4(clamp(pos, 0.0f, 1.0f), 1.0);	\n\
}";//clamp ira tirar os valores negativos

//Fragment shader
static const char *fragment_shader = "				\n\
#version 330 										\n\
													\n\
in vec4 vertexCol;									\n\
out vec4 colour;  									\n\
													\n\
void main(){										\n\
	colour = vertexCol;								\n\
}";	

GLuint VBO, VAO, shader, uniformModel;
const GLint WIDTH = 800, HEIGHT = 600;

void create_triangle(){
	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void add_shadder(GLuint theProgram, const char* shaderCode, GLenum shaderType){
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(theShader, 1024, NULL, eLog);
		fprintf(stderr, "Error compiling the %d shader: '%s'\n", shaderType, eLog);
		return;
	}

	glAttachShader(theProgram, theShader);
}

void CompileShaders(){
	shader = glCreateProgram();

	if (!shader) {
		printf("Failed to create shader\n");
		return;
	}

	add_shadder(shader, vertex_shader, GL_VERTEX_SHADER);
	add_shadder(shader, fragment_shader, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", eLog);
		return;
	}

	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
		return;
	}

	uniformModel = glGetUniformLocation(shader, "model");
}

int main(){
	if(!init_glfw(3,3)){return -1;}//ponto de saida 1

	GLFWwindow *mainWindow = create_window(WIDTH,HEIGHT, "Teste", NULL, NULL);
	if(!mainWindow){return -2;}//ponto de saida 2

	if(!init_glew(mainWindow)){return -3;}//ponto de saida 3

	create_triangle();
	CompileShaders();

	while (!glfwWindowShouldClose(mainWindow))
	{
		glfwPollEvents();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader);

			glm::mat4 model(1.0f); //matriz identidade

			model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.0f)); //transformado a matriz dentidade em uma matriz para escalar por 0.4
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

			glBindVertexArray(VAO);
				glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(0);

		glUseProgram(0);

		glfwSwapBuffers(mainWindow);
	}

	glfwDestroyWindow(mainWindow);
	glfwTerminate();

	return 0;
}