#include <GL/glew.h>
#include <GLFW/glfw3.h>

bool init_glfw(int major_version, int minor_version);
GLFWwindow *create_window(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share);
bool init_glew(GLFWwindow *window_for_context);