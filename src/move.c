#include <move.h>

/****** MOVE *******/

/**
 * @brief Initializes Move
 * @param move Move to initialize
 * @param start_square Starting Square of Piece
 * @param dest_square Square where piece will end up after move
 */
void initMove( Move * p_move, Square * p_start_square, Square * p_dest_square ) {
    p_move->start_square = p_start_square;
    p_move->dest_square = p_dest_square;
    p_move->piece = p_start_square->piece;
}

/****** MOVE NODE *******/
/**
 * @brief Initializes Movenode
 * @param move_node Movenode to initialize
 * @param root_node Root to Movelist
 * @return move_node Pointer to allocated MoveNode Instance
 */
MoveNode * initMoveNode( MoveNode * p_root, Move * p_move ) {
    // Check if rootnode is initialized
    MoveNode * move_node = (MoveNode *)malloc( sizeof( MoveNode ) );

    // Set parameteres
    move_node->prev = NULL;
    move_node->next = NULL;
    move_node->move = p_move;
    move_node->root = p_root;

    return move_node;
}

/**
 * @brief Appends move to move_node
 * @param move_node move_node to append another move_node to
 * @param move Move to append
 */
void appendMove( MoveNode * p_move_node, Move * p_move ) {
    
    // There might not be a move in root move node
    if ( p_move_node->move == NULL ) {
        p_move_node->move = p_move;
        c_print_w( "There was a movenode not being initialised with a move F:%s l:%d\n", __FILE__, __LINE__ );
        return;
    }

    // Create new MoveNode
    MoveNode * new_node = initMoveNode( p_move_node, p_move );

    // Get Last Node to append
    MoveNode * current = p_move_node;
    while ( current->next != NULL ) current = current->next;

    // Link Nodes
    if ( current != current->root ) {
        current->next = new_node;
        new_node->prev = current;
    }

    // Initialize Value
    new_node->move = p_move;
}

/**
 * @brief Returns move at position
 * @param move_node Root move node
 * @param position Position of move in list
 * @return move Move
 */
Move * getMove( MoveNode * p_move_node, int p_position ) {
    MoveNode * current = p_move_node;
    for ( int i = 0; i < p_position; i++ ) {
        current = current->next; 
    }
    return current->move;
}

/** THIS DOES NOT WORK: IT CAUSES SEG FAULT TODO *****
 * @brief Clears a movelist of all elements and frees memory
 * @param move_node Root node of the movelist
 * @param free_moves If true also frees the memory of allocated memory for moves
 */
void clearMoveList( MoveNode * p_move_node, bool p_free_moves ) {

    // Free every movenode
    MoveNode * current = p_move_node;
    while ( current != NULL ) {
        MoveNode * temp = current;
        current = current->next;

        // Free memory
        if ( p_free_moves && temp->move != NULL ) free( temp->move );

        free( temp );
    }
}

/**
 * @brief Returns how many Moves are located in movelist
 * @param root Root movenode
 * @return count Count of how many moves are in movelist
 */
uint32 countMoveNodes( MoveNode * p_root ) {
    MoveNode * current = p_root;
    uint32 count = 0;
    while ( current != NULL ) {
        if ( current->move != NULL ) count++;
        if ( current->next != NULL ) current = current->next; 
        else break;
    }
    return count;
}

/**
 * @brief Debug print for all moves in movelist
 * @param move_list Movelist
 */
void debugPrintMoveList( MoveNode * p_move_list ) {
    MoveNode * current = p_move_list;
    while ( current != NULL ) {
        Move * move = current->move;
        if ( move == NULL ) {
            c_print_err( "Uninitialised move was supposed to be printed from movenode %p\n", current );
            break;
        }
        printf( "Move would move piece:%c from \n \t£X:%dY:%d To \n\tX:%dY:%d\n", 
                move->piece->symbol, 
                move->start_square->x, 
                move->start_square->y, 
                move->dest_square->x, 
                move->dest_square->y );
        if ( current->next != NULL ) current = current->next;
        else break;
    }
}
