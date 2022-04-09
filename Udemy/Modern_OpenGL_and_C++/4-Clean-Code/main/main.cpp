#include "window.h"
#include <vector>
#include "mesh.h"
#include "shader.h"

//Vertex Shader
static const char *vertex_shader = "./shaders/shader.vert";

//Fragment shader
static const char *fragment_shader = "./shaders/shader.frag";

const GLint WIDTH = 800, HEIGHT = 600;

std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;

void create_objects(){	
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

	Mesh *obj1 = new Mesh();
	obj1->create_mesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->create_mesh(vertices, indices, 12, 12);
	meshList.push_back(obj2);
}

void create_shaders(){
	Shader *shader1 = new Shader();
	shader1->create_from_files(vertex_shader, fragment_shader);
	shaderList.push_back(shader1);
}

int main(){
	if(!init_glfw(3,3)){return -1;}//ponto de saida 1
	GLFWwindow *mainWindow = create_window(WIDTH,HEIGHT, "Teste", NULL, NULL);
	if(!mainWindow){return -2;}//ponto de saida 2
	if(!init_glew(mainWindow)){return -3;}//ponto de saida 3

	int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	create_objects();
	create_shaders();

	GLuint uniformModel = shaderList[0]->get_model_location();
	GLuint uniformProjection = shaderList[0]->get_projection_location();
	
	float aspect_ratio = (float)bufferWidth/(float)bufferHeight;
	glm::mat4 projection = glm::perspective(45.0f, aspect_ratio, 0.1f, 100.0f);

	float rads = 0.0f;
	while (!glfwWindowShouldClose(mainWindow)){
		glfwPollEvents();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0]->use_shader();

			glm::mat4 model(1.0f);
			model = glm::translate(model, glm::vec3(0.0f, 0.5f, -3.5f));
			model = glm::rotate(model, rads, glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
			meshList[0]->render_mesh();

			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(-0.5f, 1.0f, -2.5f));
			model = glm::rotate(model, rads, glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			meshList[1]->render_mesh();
	
		shaderList[0]->stop_using_shader();
		rads += 0.0005;
		glfwSwapBuffers(mainWindow);
	}

	glfwDestroyWindow(mainWindow);
	glfwTerminate();

	return 0;
}