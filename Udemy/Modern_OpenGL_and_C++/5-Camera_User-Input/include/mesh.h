#pragma once //serve para fazer com que o ficheiro atual apenas seja incluído uma vez durante o processo de compilação

#include <GL/glew.h>

class Mesh{
    public:
        Mesh();
        void create_mesh(GLfloat *vertices, unsigned int *indices, unsigned int num_vertices, unsigned int num_indices);
        void render_mesh();
        void clear_mesh();
        ~Mesh();

    private:
        GLuint VAO, VBO, IBO;
        GLsizei indexCount;
};