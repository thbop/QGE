// Standard includes
#include "stdio.h"
#include "stdbool.h"

// OpenGL stuff
#include "glad/glad.h"
#include "GLFW/glfw3.h"

// My stuff
#include "tfile.h"
#include "shader.h"


// Context
struct {
    GLFWwindow *window;
} ctx;

// Colors
typedef struct {
    float r, g, b, a;
} Color;

#define BLACK (Color){ 0.0f, 0.0f, 0.0f, 1.0f }
#define WHITE (Color){ 1.0f, 1.0f, 1.0f, 1.0f }
#define RED   (Color){ 1.0f, 0.0f, 0.0f, 1.0f }
#define GREEN (Color){ 0.0f, 1.0f, 0.0f, 1.0f }
#define BLUE  (Color){ 0.0f, 0.0f, 1.0f, 1.0f }

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
    
    // glViewport( 0, 0, width, height );
    
    return true;
}

// if window should close
#define WindowShouldClose() \
    glfwWindowShouldClose( ctx.window )

// Clears the screen as a specific color
void ClearWindow( Color color ) {
    glClearColor( color.r, color.g, color.b, color.a );
    glClear( GL_COLOR_BUFFER_BIT );
}

// Close window
void CloseWindow() {
    glfwTerminate();
}