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

#ifndef SHADER_H
#define SHADER_H


typedef unsigned int ShaderHandle;

// Opens a shader of a given type, compiles it, prints any errors.
// Types:
//     GL_VERTEX_SHADER
//     GL_FRAGMENT_SHADER
ShaderHandle CompileShader( const char *sourceFileName, int type ) {
    // Open file
    const char *shaderSource = TFileOpen( sourceFileName );

    // Create and compile
    ShaderHandle shader = glCreateShader( type );
    glShaderSource( shader, 1, &shaderSource, NULL );
    glCompileShader( shader );
    
    // Check for errors
    int success;
    char infoLog[512];
    glGetShaderiv( shader, GL_COMPILE_STATUS, &success );
    if ( !success ) {
        glGetShaderInfoLog( shader, 512, NULL, infoLog );
        printf("[ERROR] Shader compile error for \"%s\":\n%s\n", sourceFileName, infoLog);
    }
    free( (char*)shaderSource );
    
    return shader;
}

// Loads a shader program
ShaderHandle LoadShaderProgram( const char *vertFileName, const char *fragFileName ) {
    // Compile vertex and fragment shaders
    ShaderHandle vertexShader   = CompileShader( vertFileName, GL_VERTEX_SHADER );
    ShaderHandle fragmentShader = CompileShader( fragFileName, GL_FRAGMENT_SHADER );

    // Create program and link vertex and fragment shaders into it
    ShaderHandle program = glCreateProgram();
    glAttachShader( program, vertexShader );
    glAttachShader( program, fragmentShader );
    glLinkProgram( program );

    // Destroy old shader objects
    glDeleteShader( vertexShader );
    glDeleteShader( fragmentShader );

    // Check for linking errors
    int success;
    char infoLog[512];
    glGetProgramiv( program, GL_LINK_STATUS, &success );
    if ( !success ) {
        glGetProgramInfoLog( program, 512, NULL, infoLog );
        printf( "[ERROR] Failed to link \"%s\" and \"%s\" into program:\n%s", vertFileName, fragFileName, infoLog );
    }

    return program;
}

void ShaderUniform1f( ShaderHandle shader, const char *name, float value ) {
    int location = glGetUniformLocation( shader, name );
    glUniform1f( location, value );
}

void ShaderUniform2f( ShaderHandle shader, const char *name, vec2s value ) {
    int location = glGetUniformLocation( shader, name );
    glUniform2f( location, value.x, value.y );
}

void ShaderUniform3f( ShaderHandle shader, const char *name, vec3s value ) {
    int location = glGetUniformLocation( shader, name );
    glUniform3f( location, value.x, value.y, value.z );
}

void ShaderUniform4f( ShaderHandle shader, const char *name, vec4s value ) {
    int location = glGetUniformLocation( shader, name );
    glUniform4f( location, value.x, value.y, value.z, value.w );
}

void ShaderUniformMatrix4f( ShaderHandle shader, const char *name, mat4s value ) {
    int location = glGetUniformLocation( shader, name );
    glUniformMatrix4fv( location, 1, GL_FALSE, (float*)&value );
}

#endif