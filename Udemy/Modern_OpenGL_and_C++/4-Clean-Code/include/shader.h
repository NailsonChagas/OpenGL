#pragma once

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>

#include <GL/glew.h>

class Shader{
    public:
        Shader();

        void create_from_string(const char *vertex_code, const char *fragment_code);
        void create_from_files(const char *vertex_path, const char *fragment_path);

        std::string read_file(const char *file_path);

        GLuint get_projection_location();
        GLuint get_model_location();

        void use_shader();
        void stop_using_shader();
        void clear_shader();

        ~Shader();
    
    private:
        GLuint shaderID, uniformProjection, uniformModel;

        void compile_shader(const char *vertex_code, const char *fragment_code);
        void add_shader(GLuint shader_program, const char *shader_code, GLenum shader_type);

};