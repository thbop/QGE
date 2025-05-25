#include "qge.h"

int main() {
    CreateWindow( "Hello World OpenGL", 640, 480 );

    // Vertex buffer
    float verticies[] = {
        // positions         colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f, // top 
    };

    unsigned int indices[] = {
        0, 1, 2,
    };

    unsigned int vao, ebo, vbo;
    glGenVertexArrays( 1, &vao );
    glGenBuffers( 1, &vbo );
    glGenBuffers( 1, &ebo );

    glBindVertexArray( vao );
    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData( GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW );
    
    // position attribute
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0 );
    glEnableVertexAttribArray( 0 );

    // color attribute
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)) );
    glEnableVertexAttribArray( 1 );

    // Shader stuff
    ShaderHandle shader = LoadShaderProgram( "shaders/core.vert", "shaders/core.frag" );
    
    // Loop until the user closes the window
    while ( !WindowShouldClose() ) {
        // Drawing
        ClearWindow( BLACK );
        
        glUseProgram( shader );
        glBindVertexArray( vao );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
        glDrawElements( GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)0 );

        // Swap front and back buffers
        glfwSwapBuffers( ctx.window );

        // Poll for and process events
        glfwPollEvents();
    }
    glDeleteShader( shader );
    CloseWindow();
    return 0;
}