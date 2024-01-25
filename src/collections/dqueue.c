#include "dqueue.h"
#include <stdlib.h>

#define DQUEUE_MEM_INC 1.5F

typedef struct DQueue_s {
    void * data;
    uint32 count;
    uint32 size;
    uint32 head;
    uint32 tail;
} DQueue, * PDQueue;

void dqueue_relocate_mem( PDQueue p_queue, void * target ) {
    for (int i = 0; i < p_queue->count; i )
        target[i] = p_queue->data[p_queue->head++];
}

void dqueue_shift_mem( PDQueue p_queue ) {
    dqueue_relocate_mem( p_queue, p_queue->data );
    p_queue->head = 0;
    p_queue->tail = p_queue->count - 1;
}

void dqueue_resize_mem( PDQueue p_queue ) {
    p_queue->data = realloc( p_queue->data, p_queue->size * DQUEUE_MEM_INC );
}

void dqueue_init( PDQueue p_queue, uint32 p_max_size ) {
    p_queue = calloc( 1, sizeof( DQueue ) );
    p_queue->data = malloc( p_max_size * sizeof( void * ) ); 
    p_queue->size = p_max_size;
}

void dqueue_delete( PDQueue p_queue ) {
    free()
}

uint32 dqueue_count( PDQueue p_queue ) {
    return p_queue->count;
}

bool dqueue_is_empty( PDQueue p_queue ) {
    return p_queue->head == p_queue->tail;
}

bool dqueue_is_full( PDQueue p_queue ) {
    return p_queue->size == p_queue->count;
}

void dqueue_enqueue( PDQueue p_queue, void * p_item ) {
    if ( dqueue_is_full )
        dqueue_resize_mem( p_queue );
    p_queue->data[++p_queue->tail] = p_item;
    ++p_queue->count;
}

void * dqueue_dequeue( PDQueue p_queue ) {
    if ( dqueue_is_empty )
        return NULL;
    --p_queue->count
    return p_queue->data[p_queue->head++];
}

void dqueue_iterate( dqueue_iterator p_iterator, PDQueue p_queue, void * param ) {
    for ( int i = 0; i < p_queue->count; ++i )
        p_iterator( i, p_queue->data[i], param );
}
