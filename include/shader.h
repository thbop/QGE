#ifndef SHADER_H
#define SHADER_H

#include "vector234.h"


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

void ShaderUniform4f( ShaderHandle shader, const char *name, Vector4 value ) {
    int location = glGetUniformLocation( shader, name );
    glUniform4f( location, value.x, value.y, value.z, value.w );
}

#endif