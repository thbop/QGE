#ifndef TSTRING_H
#define TSTRING_H

// My custom string functions

#include "string.h"
#include "stdlib.h"

#include "list_t.h"

// Returns a heap-allocated substring given a string, a starting pos,
// and the number of characters to copy over (len).
// Returns NULL if the input is invalid
char *TStringSubStr( char *string, int pos, int len ) {
    // Check for invalid conditions
    if ( string == NULL ) return NULL;
    if ( pos < 0 || len < 0 ) return NULL;
    if ( strlen( string ) < pos + len ) return NULL;

    // Allocate new buffer and copy
    char *buffer = (char*)malloc( len + 1 );
    buffer[len] = '\0';

    strncpy( buffer, string + pos, len );


    return buffer;
}

// Splits a given null-terminated string by a given char
// Returns a list of strings excluding the separator
list_t TStringSplit( char *string, char separator ) {
    list_t list = new_list();


    return list;
}

#endif