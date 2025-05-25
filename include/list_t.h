#ifndef LIST_T_H
#define LIST_T_H

#include "stdio.h"
#include "string.h"
#include "stdlib.h"


void *_qalloc(void *value, size_t size) {
    void *v_ptr = malloc(size);
    memcpy(v_ptr, value, size);
    return v_ptr;
}

// Given a stack-allocated variable (no literals), quick allocate will allocate
// and copy that variable to the heap, returning a pointer.
#define qalloc(value) \
    _qalloc(&value, sizeof(value))

// A list node
typedef struct {
    void *value;
    void *prev, *next;
} l_node;

// A list type
typedef struct {
    l_node *head;
    size_t len;
} list_t;

// Returns an empty new list
list_t new_list() {
    return (list_t){
        .head = NULL,
        .len  = 0,
    };
}


void *_list_append(list_t *list, void *value) {
    l_node *n = (l_node*)malloc(sizeof(l_node));
    n->value = value;
    n->prev  = 
    n->next  = NULL;

    if (list->head == NULL)
        list->head = n;
    else {
        list->head->prev = n;
        n->next = list->head;
        list->head = n;
    }

    list->len++;
    return value;
}

// Appends a stack-allocated variable to a given list.
#define list_append(list, value) \
    _list_append(&list, qalloc(value))

// Given a list and an iterator name, iterates through a list.
// You can access list value pointer by casting and dereferencing `it->value`
// Example:
//    `*(int*)int->value`
#define list_foreach(list, it) \
    for ( l_node *it = list.head; it != NULL; it = it->next )

// Same as `list_foreach`, but takes a list_t pointer.
#define list_ptr_foreach(list_ptr, it) \
    for ( l_node *it = list->head; it != NULL; it = it->next )

l_node *_list_find(list_t *list, void *value) {
    list_ptr_foreach(list, n) {
        if ( n->value == value ) return n;
    }
    return NULL;
}

#define list_find(list, value_ptr) \
    _list_find(&list, value_ptr)

// Removes an element from the list, but does not free its value.
// Instead, it returns the value
void *_list_pop( list_t *list, l_node *popped ) {
    if ( popped == NULL ) return NULL;
    
    if ( popped->prev == NULL ) {
        if ( popped->next == NULL )               // PREV = NEXT = NULL
            list->head = NULL;
        else {                                     // PREV = NULL; NEXT = PTR
            list->head = popped->next;
            list->head->prev = NULL;
        }
    }
    else {
        if ( popped->next == NULL )               // PREV = PTR; NEXT = NULL
            ((l_node*)popped->prev)->next = NULL;
        else {                                     // PREV = PTR; NEXT = PTR
            l_node *prev = popped->prev;
            l_node *next = popped->next;

            prev->next = next;
            next->prev = prev;
        }
    }
    list->len--;
    void *value = popped->value;
    free(popped);
    return value;
}

void _list_remove(list_t *list, l_node *removed) {
    void *value = _list_pop( list, removed );
    if ( value != NULL )
        free(value);
}

#define list_remove(list, item) \
    _list_remove(&list, item)

// Frees the list, but not its elements
void _list_disband( list_t *list ) {
    l_node *node = list->head;
    l_node *n;
    while (node != NULL) {
        n = node->next;
        free(node);
        node = n;
    }
    *list = new_list();
}

void _list_free(list_t *list) {
    list_ptr_foreach( list, it ) {
        free( it->value );
    }
    _list_disband( list );
}

#define list_free( list ) \
    _list_free( &list )

#endif