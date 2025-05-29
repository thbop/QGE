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
    int
        width  = 640,
        height = 480;
    
    CreateWindow( "Hello World OpenGL", width, height );

    Model *model = LoadModel( "models/rubix.obj" );

    unsigned int vao, ebo, vbo;
    glGenVertexArrays( 1, &vao );
    glGenBuffers( 1, &vbo );
    glGenBuffers( 1, &ebo );

    glBindVertexArray( vao );
    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData( GL_ARRAY_BUFFER, vector_sizeof_elements( model->vertices ), model->vertices.buffer, GL_STATIC_DRAW );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, vector_sizeof_elements( model->indices ), model->indices.buffer, GL_STATIC_DRAW );
    
    // Position attribute
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0 );
    glEnableVertexAttribArray( 0 );

    // Color attribute
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)) );
    glEnableVertexAttribArray( 1 );

    // Texture coordinate attribute
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)) );
    glEnableVertexAttribArray( 2 );

    // Shader stuff
    ShaderHandle shader = LoadShaderProgram( "shaders/core.vert", "shaders/core.frag" );

    // Texture stuff
    Texture texture = LoadTexture( "textures/rubix.png" );

    // Projection
    mat4s view = glms_mat4_identity();
    view = glms_translate( view, (vec3s){{ 0.0f, 0.0f, -5.0f }} );
    
    mat4s projection = glms_perspective( glm_rad( 45.0f ), (float)width / (float)height, 0.1f, 100.0f );

    
    // Loop until the user closes the window
    while ( !WindowShouldClose() ) {
        // Update
        if ( glfwGetKey( ctx.window, GLFW_KEY_W ) == GLFW_PRESS )
            view = glms_translate( view, (vec3s){{ 0.0f, 0.0f, 0.04f }} );
        if ( glfwGetKey( ctx.window, GLFW_KEY_S ) == GLFW_PRESS )
            view = glms_translate( view, (vec3s){{ 0.0f, 0.0f, -0.04f }} );
        if ( glfwGetKey( ctx.window, GLFW_KEY_A ) == GLFW_PRESS )
            view = glms_translate( view, (vec3s){{ 0.04f, 0.0f, 0.0f }} );
        if ( glfwGetKey( ctx.window, GLFW_KEY_D ) == GLFW_PRESS )
            view = glms_translate( view, (vec3s){{ -0.04f, 0.0f, 0.0f }} );

        mat4s modelTransform = glms_mat4_identity();
        modelTransform = glms_rotate( modelTransform, sinf( (float)glfwGetTime() ), (vec3s){{ 0.0f, 1.0f, 0.0f }} );


        // Drawing
        ClearWindow( BLACK );
        
        glUseProgram( shader );
        ShaderUniformMatrix4f( shader, "model", modelTransform );
        ShaderUniformMatrix4f( shader, "view", view );
        ShaderUniformMatrix4f( shader, "projection", projection );

        glBindTexture( GL_TEXTURE_2D, texture.handle );

        glBindVertexArray( vao );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );

        glDrawElements( GL_TRIANGLES, model->indices.elementCount, GL_UNSIGNED_INT, (void*)0 );

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