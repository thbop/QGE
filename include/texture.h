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

#ifndef TEXTURE_H
#define TEXTURE_H

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

// GPU-Texture
typedef struct {
    int width, height;
    unsigned int handle;
} Texture;

// Loads a texture from a file and uploads it to the VRAM
Texture LoadTexture( const char *fileName ) {
    int nrChannels;
    Texture texture;

    // Load texture
    unsigned char *data = stbi_load(
        fileName,
        &texture.width,
        &texture.height,
        &nrChannels, 0
    );

    // Check if it loaded properly
    if ( data == NULL ) {
        printf( "[ERROR] Failed to load texture \"%s\"!\n", fileName );
        return texture;
    }

    // To the GPU
    glGenTextures( 1, &texture.handle );
    glBindTexture( GL_TEXTURE_2D, texture.handle );
    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGBA,
        texture.width, texture.height,
        0, GL_RGBA, GL_UNSIGNED_BYTE, data
    );
    glGenerateMipmap( GL_TEXTURE_2D );

    stbi_image_free( data );

    return texture;
}


#endif