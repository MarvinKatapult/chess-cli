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

typedef struct s_MoveList {
    uint32 count_moves;
    Move * moves;
    #define MAX_NUMBER_MOVES    27
} MoveList;

/**
 * @brief Initializes a Movelist with a given size (Maybe just use MAX_NUMBER_MOVES)
 * @note This function allocates memory that needs to be freed with free MoveList->moves
 * @param moves MoveList Instance
 * @param size Number of Moves fit in the list
 */
void initMoveList( MoveList * moves, uint32 count );

/**
 * @brief Initializes a Move
 * @param move Move
 * @param start_x Start X
 * @param start_y Start Y
 * @param dest_x Destination X
 * @param dest_y Destination Y
 * @param piece Piece to move
 */
void initMove( Move * move, uint32 start_x, uint32 start_y, uint32 dest_x, uint32 dest_y, Piece * piece );

/**
 * @brief Wrapper for adding move to a movelist
 *        also increments count in MoveList
 * @param moves MoveList Instance
 * @param move Move to add
 * @param index Position where to store move
 */
void addMove( MoveList * moves, Move move, uint32 index );

#endif
