#include "shader.h"

Shader::Shader(){
    shaderID = 0;
    uniformModel = 0;
    uniformProjection = 0;
}

void Shader::create_from_string(const char *vertex_code, const char *fragment_code){
    compile_shader(vertex_code, fragment_code);
}

std::string Shader::read_file(const char *file_path){
	std::string content;
	std::ifstream fileStream(file_path, std::ios::in);

	if(!fileStream.is_open()){
		std::cout << "Failed to read " << file_path << " File doesn't exist" << std::endl;
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()){
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

void Shader::create_from_files(const char *vertex_path, const char *fragment_path){
	std::string vertex_string = read_file(vertex_path);
	std::string fragment_string = read_file(fragment_path);
	const char* vertex_code = vertex_string.c_str();
	const char* fragment_code = fragment_string.c_str();

	compile_shader(vertex_code, fragment_code);
}

void Shader::compile_shader(const char *vertex_code, const char *fragment_code){
    shaderID = glCreateProgram();

	if (!shaderID) {
		printf("Failed to create shader\n");
		return;
	}

	add_shader(shaderID, vertex_code, GL_VERTEX_SHADER);
	add_shader(shaderID, fragment_code, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", eLog);
		return;
	}

	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
		return;
	}

	uniformModel = glGetUniformLocation(shaderID, "model");
	uniformProjection = glGetUniformLocation(shaderID, "projection");
}

GLuint Shader::get_projection_location(){
    return uniformProjection;
}

GLuint Shader::get_model_location(){
    return uniformModel;
}

void Shader::use_shader(){
    glUseProgram(shaderID);
}

void Shader::stop_using_shader(){
    glUseProgram(0);
}

void Shader::clear_shader(){
    if(shaderID != 0){
        glDeleteProgram(shaderID);
        shaderID = 0;
    }

    uniformModel = 0;
    uniformProjection = 0;
}

void Shader::add_shader(GLuint shader_program, const char *shader_code, GLenum shader_type){
    GLuint theShader = glCreateShader(shader_type);

	const GLchar* theCode[1];
	theCode[0] = shader_code;

	GLint codeLength[1];
	codeLength[0] = strlen(shader_code);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(theShader, 1024, NULL, eLog);
		fprintf(stderr, "Error compiling the %d shader: '%s'\n", shader_type, eLog);
		return;
	}

	glAttachShader(shader_program, theShader);
}

Shader::~Shader(){
    clear_shader();
}