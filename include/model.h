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

#ifndef MODEL_H
#define MODEL_H



// Reference:
// - https://en.wikipedia.org/wiki/Wavefront_.obj_file


#include "tfile.h"
#include "tstring.h"
#include "vector_t.h"
#include "list_t.h" // for qalloc

// A CPU representation of the model to be loaded onto the GPU later
typedef struct {
    char *name;
    vector_t vertices;
    vector_t indices;
} Model;

// Returns a new empty model. `name` can be NULL
Model *NewModel( const char *name ) {
    Model model = {
        .name      = NULL,
        .vertices = new_vector( float ),
        .indices  = new_vector( unsigned int ),
    };
    if ( name != NULL )
        model.name = TStringCopy( (char*)name );
    
    
    return qalloc( model );
}

// Parses a single vertex line of a Wavefront .obj file and updates the model
// For example:
// v -1.000000 1.000000 0.000000
void _ParseModelVertexLine( Model *model, char **args ) {
    // Iterate through the three vertices
    for ( int i = 1; i < 4; i++ ) {
        float value = strtof( args[i], NULL );
        vector_append( model->vertices, value );
    }

    // The current setup requires the color after each vertex
    float
        r = 0.3,
        g = 0.4,
        b = 0.7;
    vector_append( model->vertices, r );
    vector_append( model->vertices, g );
    vector_append( model->vertices, b );
}


// Parses a single face line of a Wavefront .obj file and updates the model
// Currently only uses the vertex index
// For example:
// f 2/1/1 3/2/1 1/3/1
void _ParseModelFaceLine( Model *model, char **args ) {
    // Iterate through the three indices
    for ( int i = 1; i < 4; i++ ) {
        char *indexStr = TStringSubStr( args[i], 0, TStringFindChar( args[i], '/' ) );
        unsigned int index = atoi( indexStr ) - 1; // .obj indcies start with 1 instead of 0
        free(indexStr);

        vector_append( model->indices, index );
    }
}

// Parses a single line of a Wavefront .obj file and updates the model
// accordingly. For example:
// ```
// o Plane
// v -1.000 -1.000 -0.000
// ```
void _ParseModelLine( Model *model, char *line ) {
    int argCount;
    char **args = TStringSplit( line, ' ', &argCount );

    // If object name line, then copy only the first name
    if ( args[0][0] == 'o' && model->name == NULL )
        model->name = TStringCopy( args[1] );
    
    // If line is a vertex (v, not vt or vn)
    else if ( !strcmp( args[0], "v" ) )
        _ParseModelVertexLine( model, args );
    
    // If line is a face (f)
    else if ( args[0][0] == 'f' )
        _ParseModelFaceLine( model, args );

    TStringFreeStringArray( args, argCount );
}

// Loads the only object in a Wavefront .obj file (ensure that there is only
// one object). Also make sure that the faces are triangles.
Model *LoadModel( const char *modelFileName ) {
    char *data = TFileOpen( modelFileName );
    if ( data == NULL )
        return NULL;

    int lineCount;
    char **lines = TStringSplit( data, '\n', &lineCount );

    Model *model = NewModel( NULL );

    for ( int i = 0; i < lineCount; i++ )
        _ParseModelLine( model, lines[i] );

    TStringFreeStringArray( lines, lineCount );
    free( data );

    return model;
}

// Frees and deletes a model
void UnloadModel( Model *model ) {
    if ( model == NULL ) return;

    if ( model->name != NULL )
        free( model->name );
    
    vector_free( model->vertices );
    vector_free( model->indices );

    free( model );
}

#endif