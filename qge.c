#include "qge.h"

int main() {
    CreateWindow( "Hello World OpenGL", 640, 480 );

    // Vertex buffer
    float verticies[] = {
        -0.5f, -0.5f,  0.0f,
         0.5f, -0.5f,  0.0f,
         0.0f,  0.5f,  0.0f
    };

    unsigned int vbo;
    glGenBuffers( 1, &vbo );
    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData( GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW );

    // Shader stuff
    LoadShaderProgram( "shaders/core.vert", "shaders/core.frag" );


    // Loop until the user closes the window
    while ( !WindowShouldClose() ) {
        // Drawing
        ClearWindow( BLACK );

        

        // Swap front and back buffers
        glfwSwapBuffers( ctx.window );

        // Poll for and process events
        glfwPollEvents();
    }

    CloseWindow();
    return 0;
}