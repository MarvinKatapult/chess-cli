#ifndef _COLLECTIONS_DQUEUE_H_
#define _COLLECTIONS_DQUEUE_H_

#include "tdef.h"

/**
 * @brief Object holding the queue information
 */
typedef struct DQueue_s DQueue, * PDQueue;

/**
 * @brief Function pointer for iterating through the queue
 */
typedef void ( *dqueue_iterator )( int index, void * item, void * param);

/**
 * @brief Initializes a queue object
 * 
 * @param queue Object to initialize. If it already contains an object, it will get a new object
 * @param max_size Maximum number of items before it needs resizing
 */
void dqueue_init( PDQueue queue , uint32 max_size );

/**
 * @brief Deletes a queue object
 * 
 * @param queue Object to delete
 */
void dqueue_delete( PDQueue queue );

/**
 * @brief 
 * 
 * @param queue 
 * @return uint32 
 */
uint32 dqueue_size( PDQueue queue );

bool dqueue_is_empty( PDQueue queue );

bool dqueue_is_full( PDQueue queue );

void dqueue_enqueue( PDQueue queue, void * item );

void * dqueue_dequeue( PDQueue queue );

void dqueue_iterate( PDQueue queue, dqueue_iterator iterator, void * param );

#endif