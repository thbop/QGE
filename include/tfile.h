#ifndef TFILE_H
#define TFILE_H

// A simple file opening utility

#include "stdio.h"
#include "stdlib.h"

// Opens a file and returns a heap-allocated, null-terminated buffer with its
// contents.
char *TFileOpen( const char *fileName ) {
    FILE *fp = fopen( fileName, "r" );

    // Get file size
    fseek( fp, 0, SEEK_END );
    long size = ftell( fp ) + 1; // +1 for the null terminator
    fseek( fp, 0, SEEK_SET );

    // Allocate buffer
    char *buffer = (char*)malloc( size );
    buffer[size - 1] = '\0'; // Set null terminator

    // Read into buffer
    fread( buffer, sizeof(char), size, fp );

    fclose( fp );
    
    return buffer;
}

#endif