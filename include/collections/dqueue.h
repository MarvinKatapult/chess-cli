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
 * @param queue Queue to initialize. If it already contains an object, it will get a new object
 * @param max_size Maximum number of items before it needs resizing
 */
void dqueue_init( PDQueue queue , uint32 max_size );

/**
 * @brief Deletes a queue object
 * 
 * @param queue Queue to delete
 */
void dqueue_delete( PDQueue queue );

/**
 * @brief Gives the item count of a queue
 * 
 * @param queue Queue to get the count from
 * @return uint32 Item count of the queue
 */
uint32 dqueue_count( PDQueue queue );

/**
 * @brief Checks if the queue is empty
 * 
 * @param queue Queue to check
 * @return bool True, if the queue is empty, otherwise false
 */
bool dqueue_is_empty( PDQueue queue );

/**
 * @brief Checks if the queue is full
 * 
 * @param queue Queue to check
 * @return bool True, if the queue is full, otherwise false 
 */
bool dqueue_is_full( PDQueue queue );

/**
 * @brief Adds an item at the end of a queue
 * 
 * @param queue Queue to add to
 * @param item Item to add
 */
void dqueue_enqueue( PDQueue queue, void * item );

/**
 * @brief Pops the item from the beginning of the queue
 * 
 * @param queue Queue to de-queue from
 * @return void* First item of the queue
 */
void * dqueue_dequeue( PDQueue queue );

/**
 * @brief Iterates through the queue and calls the delegate function provided to work with the iteration
 * 
 * @param queue Queue to iterate through
 * @param iterator Delegate function called for every item in the iteration
 * @param param optional pointer to custom objects for result containment or other uses.
 */
void dqueue_iterate( PDQueue queue, dqueue_iterator iterator, void * param );

#endif