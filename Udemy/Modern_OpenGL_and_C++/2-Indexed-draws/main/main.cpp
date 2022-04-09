#include "window.h"

/*----------- Indexed Draws -----------
- usando o mesmo vertice varias vezes para desenhar figuras mais complexas (ex: piramede)
*/

//primeiro 3D

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

GLuint VBO, VAO, IBO, shader, uniformModel; //ibo index buffer object
const GLint WIDTH = 800, HEIGHT = 600;

void create_triangle(){
	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f
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

void create_pyramid(){	
	unsigned int indices[] = { 
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2 
	};

	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

			glGenBuffers(1, &VBO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

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

	glEnable(GL_DEPTH_TEST);

	create_pyramid();
	CompileShaders();

	float rads = 0.0f;

	while (!glfwWindowShouldClose(mainWindow)){
		glfwPollEvents();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(shader);

			glm::mat4 model(1.0f);
			model = glm::rotate(model, rads, glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

			glBindVertexArray(VAO);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
					glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

		glUseProgram(0);

		rads += 0.001f;
		glfwSwapBuffers(mainWindow);
	}

	glfwDestroyWindow(mainWindow);
	glfwTerminate();

	return 0;
}