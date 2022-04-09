#include "window.h"
#include <vector>
#include "mesh.h"
#include "shader.h"

#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_glfw.h"
#include "ImGUI/imgui_impl_opengl3.h"

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
		0, 1, 2,
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


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(mainWindow, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	float tamanho = 0.4f;
	float rotX = 0.0f, rotY = 0.0f, rotZ = 0.0f;
	bool desenhar = true;

	while (!glfwWindowShouldClose(mainWindow)){
		glfwPollEvents();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//gerando frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();


		if(desenhar){
			shaderList[0]->use_shader();

			glm::mat4 model(1.0f);
			model = glm::translate(model, glm::vec3(0.0f, 0.5f, -3.5f));
			model = glm::rotate(model, rotX*0.01745f, glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, rotY*0.01745f, glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, rotZ*0.01745f, glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model, glm::vec3(tamanho, tamanho, tamanho));

			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
			meshList[0]->render_mesh();
	
			shaderList[0]->stop_using_shader();
		}


		ImGui::Begin("Testando ImGUI");
		ImGui::Text("Teste de texto");
		ImGui::Checkbox("Desenhar objeto", &desenhar);
		ImGui::SliderFloat("tamanho", &tamanho, 0.4f, 2.0f);
		ImGui::SliderFloat("X", &rotX, 0.0f, 360.0f);
		ImGui::SliderFloat("Y", &rotY, 0.0f, 360.0f);
		ImGui::SliderFloat("Z", &rotZ, 0.0f, 360.0f);
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(mainWindow);
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(mainWindow);
	glfwTerminate();

	return 0;
}