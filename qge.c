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

#include "qge.h"

int main() {
    CreateWindow( "Hello World OpenGL", 640, 480 );

    Model *model = LoadModel( "models/rubix.obj" );
    
    for ( int i = 0; i < model->verticies.elementCount; i++ )
        printf( "%f ", vector_at( float, model->verticies, i ) );
    
    puts("\n");
    
    for ( int i = 0; i < model->indicies.elementCount; i++ )
        printf( "%d ", vector_at( int, model->indicies, i ) );


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

    // Clean up
    UnloadModel( model );
    glDeleteShader( shader );
    CloseWindow();
    return 0;
}