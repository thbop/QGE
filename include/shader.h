#ifndef SHADER_H
#define SHADER_H

typedef struct {
    int a;
} Shader;

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

Shader LoadShaderProgram( const char *vertFileName, const char *fragFileName ) {
    ShaderHandle vertexShader   = CompileShader( vertFileName, GL_VERTEX_SHADER );
    ShaderHandle fragmentShader = CompileShader( fragFileName, GL_FRAGMENT_SHADER );

    
}

#endif