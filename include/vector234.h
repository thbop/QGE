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

#ifndef VECTOR234_H
#define VECTOR234_H

// Vector2
typedef struct {
    float x, y;
} Vector2;

// Vector3
typedef struct {
    float x, y, z;
} Vector3;

// Vector4
typedef struct {
    float x, y, z, w;
} Vector4;

// Prints a Vector2
void PrintVector2( Vector2 v ) {
    printf( "[ %f %f ]", v.x, v.y );
}

// Prints a Vector3
void PrintVector3( Vector3 v ) {
    printf( "[ %f %f %f ]", v.x, v.y, v.z );
}

// Prints a Vector4
void PrintVector4( Vector4 v ) {
    printf( "[ %f %f %f %f ]", v.x, v.y, v.z, v.w );
}

#endif