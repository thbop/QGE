/*
* Copyright © 2025 Thbop
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy of
* this software and associated documentation files (the “Software”), to deal in
* the Software without restriction, including without limitation the rights to
* use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
* of the Software, and to permit persons to whom the Software is furnished to do
* so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

// Standard includes
#include "stdio.h"
#include "stdbool.h"
#include "math.h"

// OpenGL stuff
#include "glad/glad.h"
#include "GLFW/glfw3.h"

// cglm
#include "cglm/struct.h"

// Definitions
#define QGE_POSITION_STRIDE 3
#define QGE_COLOR_STRIDE    3
#define QGE_TEXCOORD_STRIDE 2

// Colors
typedef struct {
    float r, g, b, a;
} Color;

#define BLACK (Color){ 0.0f, 0.0f, 0.0f, 1.0f }
#define WHITE (Color){ 1.0f, 1.0f, 1.0f, 1.0f }
#define RED   (Color){ 1.0f, 0.0f, 0.0f, 1.0f }
#define GREEN (Color){ 0.0f, 1.0f, 0.0f, 1.0f }
#define BLUE  (Color){ 0.0f, 0.0f, 1.0f, 1.0f }

// My stuff
#include "tfile.h"
#include "shader.h"
#include "model.h"
#include "texture.h"


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