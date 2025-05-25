#ifndef MODEL_H
#define MODEL_H

#include "tfile.h"
#include "tstring.h"

// A CPU representation of the model to be loaded onto the GPU later
typedef struct {
    char *name;
    float *verticies;
    unsigned int vertexCount;
    unsigned int *indicies;
    unsigned int indexCount;
} Model;

// Loads the only object in a Wavefront .obj file (ensure that there is only
// one object). Also make sure that the faces are triangles.
Model *LoadModel( const char *modelFileName ) {
    char *data = TFileOpen( modelFileName );
    if ( data == NULL )
        return NULL;

    int lineCount;
    char **lines = TStringSplit( data, '\n', &lineCount );

    for ( int i = 0; i < lineCount; i++ ) {

    }

    TStringFreeStringArray( lines, lineCount );
    free( data );
}

#endif