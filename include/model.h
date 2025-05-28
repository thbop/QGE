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

// A face/triangle used for building a Model
typedef struct {
    unsigned int
        vertex,
        texcoord,
        normal;
} Face;


// A more flexible model structure for building a Model
typedef struct {
    char *name;
    Color color;
    vector_t vertices;
    vector_t texCoords;
    vector_t faces;
} ModelBuild;

// Checks if an existing face matches the supplied face
// `searchDepth` determines how many elements starting from index 0 will be
// searched. This exists because this function is usually called before all
// Returns the index of the existing face if found, else returns -1
int ModelFindOrAppendFace( vector_t *faceList, Face *face, int searchDepth ) {
    int depth = faceList->elementCount;
    if ( searchDepth > -1 && searchDepth < depth )
        depth = searchDepth;

    
    for ( int i = 0; i < depth; i++ ) {
        Face *other = (Face*)_vector_at( faceList, i );
        if (
            face->vertex == other->vertex     &&
            face->texcoord == other->texcoord
        )
            return i;
    }
    // Append if the face is not found
    Face f = *face;
    _vector_append( faceList, &f );
    return -1;
}

// A CPU representation of the model to be loaded onto the GPU later
typedef struct {
    char *name;
    vector_t vertices;
    vector_t indices;
} Model;

// Returns a new empty model build. `name` can be NULL
ModelBuild *NewModelBuild( const char *name, Color color ) {
    ModelBuild model = {
        .name      = NULL,
        .color     = color,
        .vertices  = new_vector( Vector3 ),
        .texCoords = new_vector( Vector2 ),
        .faces     = new_vector( Face ),
    };
    if ( name != NULL )
        model.name = TStringCopy( (char*)name );
    
    return qalloc( model );
}

// Returns a new empty model. `name` can be NULL
Model *NewModel( const char *name ) {
    Model model = {
        .name     = NULL,
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
void _LexModelVertexLine( char **args, ModelBuild *model ) {
    switch ( args[0][1] ) {
        case '\0': { // v - vertex
            Vector3 vertex = {
                strtof( args[1], NULL ),
                strtof( args[2], NULL ),
                strtof( args[3], NULL ),
            };
            vector_append( model->vertices, vertex );
            break;
        }
        case 'n': // vn - normal
            break;
        case 't': { // vt - texture coordinate
            Vector2 texCoord = {
                strtof( args[1], NULL ),
                strtof( args[2], NULL ),
            };
            vector_append( model->texCoords, texCoord );
            break;
        }
    }
}


// Parses a single face line of a Wavefront .obj file and updates the model
// Currently only uses the vertex index
// For example:
// f 2/1/1 3/2/1 1/3/1
void _LexModelFaceLine( char **args, ModelBuild *model ) {
    // Iterate through the three indices
    for ( int i = 1; i < 4; i++ ) {
        // Get vertex attributes:
        // vertex_index/texture_index/normal_index
        int attributeCount; // 3
        char **attributes = TStringSplit( args[i], '/', &attributeCount );

        Face face = {
            // .obj indcies start with 1 instead of 0
            .vertex   = atoi( attributes[0] ) - 1,
            .texcoord = atoi( attributes[1] ) - 1,
            .normal   = atoi( attributes[2] ) - 1,
        };
        vector_append( model->faces, face );

        TStringFreeStringArray( attributes, attributeCount );
    }
}

// Parses a single line of a Wavefront .obj file and updates the model
// accordingly. For example:
// ```
// o Plane
// v -1.000 -1.000 -0.000
// ```
void _LexModelLine( char *line, ModelBuild *model ) {
    int argCount;
    char **args = TStringSplit( line, ' ', &argCount );

    // If object name line, then copy only the first name
    if ( args[0][0] == 'o' && model->name == NULL )
        model->name = TStringCopy( args[1] );
    
    // If line is a vertex (v, vt, vn)
    else if ( args[0][0] == 'v' )
        _LexModelVertexLine( args, model );
    
    // If line is a face (f)
    else if ( args[0][0] == 'f' )
        _LexModelFaceLine( args, model );

    TStringFreeStringArray( args, argCount );
}

// Frees and deletes a ModelBuild
void UnloadModelBuild( ModelBuild *model ) {
    if ( model == NULL ) return;

    if ( model->name != NULL )
        free( model->name );
    
    vector_free( model->vertices );
    vector_free( model->texCoords );
    vector_free( model->faces );

    free( model );
}

// Builds a Model from a ModelBuild
Model *_ParseModel( ModelBuild *modelBuild ) {
    Model *model = NewModel( modelBuild->name );

    int index = 0;
    int faceIndex;
    vector_t faceList = new_vector( Face );

    // Iterate through the triangle/face vertices
    for ( int i = 0; i < modelBuild->faces.elementCount; i++ ) {
        Face *face = (Face*)_vector_at( &modelBuild->faces, i );

        // Check for duplicate faces
        int existingFaceIndex = ModelFindOrAppendFace( &faceList, face, i );
        if ( existingFaceIndex != -1 )
            faceIndex = existingFaceIndex;
        else { // Create new face vertex
            faceIndex = index;

            Vector3 position = vector_at( Vector3, modelBuild->vertices, face->vertex );
            Vector2 texCoord = vector_at( Vector2, modelBuild->texCoords, face->texcoord );

            // Build face/triangle vertex
            vector_append( model->vertices, position.x );
            vector_append( model->vertices, position.y );
            vector_append( model->vertices, position.z );

            vector_append( model->vertices, modelBuild->color.r );
            vector_append( model->vertices, modelBuild->color.g );
            vector_append( model->vertices, modelBuild->color.b );

            vector_append( model->vertices, texCoord.x );
            vector_append( model->vertices, texCoord.y );

            index++;
        }

        vector_append( model->indices, faceIndex );
    }

    vector_free( faceList );

    return model;
}

// Loads the only object in a Wavefront .obj file (ensure that there is only
// one object). Also make sure that the faces are triangles.
Model *LoadModel( const char *modelFileName ) {
    char *data = TFileOpen( modelFileName );
    if ( data == NULL )
        return NULL;

    int lineCount;
    char **lines = TStringSplit( data, '\n', &lineCount );

    ModelBuild *modelBuild = NewModelBuild( NULL, WHITE );

    for ( int i = 0; i < lineCount; i++ )
        _LexModelLine( lines[i], modelBuild );

    TStringFreeStringArray( lines, lineCount );
    free( data );

    Model *model = _ParseModel( modelBuild );

    UnloadModelBuild( modelBuild );

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