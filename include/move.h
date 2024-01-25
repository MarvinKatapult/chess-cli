#ifndef __MOVE__
#define __MOVE__

#include <tdef.h>
#include <stdlib.h>

#include <piece.h>

typedef struct s_Piece Piece;

typedef struct s_Move {
    uint32 start_x;
    uint32 start_y;
    uint32 dest_x;
    uint32 dest_y;
    struct s_Piece * piece;
} Move;

/**
 * @brief Initializes Move
 * @param move Move to initialize
 * @param start_x Start x of move
 * @param start_y Start y of move
 * @param dest_x Destination x of move
 * @param dest_y Destination y of move
 * @param piece Piece to move
 */
void initMove( Move * move, uint32 start_x, uint32 start_y, uint32 dest_x, uint32 dest_y, Piece * piece );

/** MOVENODES **/
typedef struct s_MoveNode {
   struct s_MoveNode * prev; 
   struct s_MoveNode * next; 
   struct s_MoveNode * root;
   Move * move;
} MoveNode;

/**
 * @brief Initializes Movenode
 * @param move_node Movenode to initialize
 * @param root_node Root to Movelist
 * @return move_node Pointer to allocated MoveNode Instance
 */
MoveNode * initMoveNode( MoveNode * root_node, Move * move );

/**
 * @brief Appends move to move_node
 * @param move_node move_node to append another move_node to
 * @param move Move to append
 */
void appendMove( MoveNode * move_node, Move * move );

/**
 * @brief Returns move at position
 * @param move_node Root move node
 * @param position Position of move in list
 * @return move Move
 */
Move * getMove( MoveNode * move_node, int position );

/**
 * @brief Clears a movelist of all elements and frees memory
 * @param move_node Root node of the movelist
 * @param free_moves If true also frees the memory of allocated memory for moves
 */
void clearMoveList( MoveNode * move_node, bool free_moves );

/**
 * @brief Returns how many Moves are located in movelist
 * @param root Root movenode
 * @return count Count of how many moves are in movelist
 */
uint32 countMoveNodes( MoveNode * root );

/**
 * @brief Debug print for all moves in movelist
 * @param move_list Movelist
 */
void debugPrintMoveList( MoveNode * move_list );

#endif
