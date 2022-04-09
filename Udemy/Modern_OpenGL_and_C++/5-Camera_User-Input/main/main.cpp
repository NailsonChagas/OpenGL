/* ---------- Camera ----------
- camera == view space
- view space: The view space is the result of transforming your world-space 
coordinates to coordinates that are in front of the user's view.  
- usar view matrix para converter world space para view space
- view matrix precisa de 4 valore: 
	1 - posição da camera
	2 - direção(obs: vetor ira apontar para direção contraria a observada)
	3 - right: vetor apontando para direita da camera (define o eixo x)
	4 - up: vetor apontando para cima da camera
*/


//OpenGL
#include "window.h"
#include <vector>
#include "mesh.h"
#include "shader.h"
#include "input.h"
#include "camera.h"

//GUI
#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_glfw.h"
#include "ImGUI/imgui_impl_opengl3.h"

//Vertex Shader
static const char *vertex_shader = "./shaders/shader.vert";

//Fragment shader
static const char *fragment_shader = "./shaders/shader.frag";

//Camera
Camera camera;
GLfloat deltaTime = 0.0f; //usando para q a velocidade de input n seja influenciada pela velociade do processador
GLfloat lastTime = 0.0f;


const GLint WIDTH = 800, HEIGHT = 600;

std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;

void create_objects(){	
	unsigned int indices[] = { 
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		//0, 1, 2,
		0, 4, 1,
		1, 4, 2,
		2, 4, 0
	};

	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, -3.0f, 0.0f//
	};

	Mesh *obj1 = new Mesh();
	obj1->create_mesh(vertices, indices, 15, 18);
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

	Input *entrada = new Input(mainWindow);
	entrada->create_callbacks(true);

	int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	create_objects();
	create_shaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.5f);

	GLuint uniformModel = shaderList[0]->get_model_location();
	GLuint uniformProjection = shaderList[0]->get_projection_location();
	GLuint uniformView = shaderList[0]->get_view_location();
	
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
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		lastTime = now;

		glfwPollEvents();

		camera.key_control(entrada->get_keys(), deltaTime);
		camera.mouse_control(entrada->get_change_pos_X_mouse(), entrada->get_change_pos_Y_mouse());
		entrada->reset_change_mouse_pos(mainWindow); //arrumando o bug em que a camera girava sem parar

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
			glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculate_view_matrix()));
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