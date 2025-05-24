#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "stdbool.h"

// Context
struct {
    GLFWwindow *window;
} ctx;

// Initializes the window
bool CreateWindow( const char *title, int width, int height ) {
    // Initialize the library
    if ( !glfwInit() )
        return false;

    // Create a windowed mode window and its OpenGL context
    ctx.window = glfwCreateWindow( width, height, title, NULL, NULL );
    if ( !ctx.window ) {
        glfwTerminate();
        return false;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent( ctx.window );
    if ( !gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) )
        return false;
    
    return true;
}

// if window should close
#define WindowShouldClose() \
    glfwWindowShouldClose( ctx.window )


// Close window
void CloseWindow() {
    glfwTerminate();
}