#ifndef __PIECE__
#define __PIECE__

#include <tdef.h>

typedef enum {
    PAWN = 0,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
} Pieces;

typedef struct {
    uint32 start_x;
    uint32 start_y;
    uint32 dest_x;
    uint32 dest_y;
    char piece;
} Move;

typedef struct {
    uint32 count_moves;
    Move * moves;
    #define MAX_NUMBER_MOVES    27
} MoveList;

/**
 * @brief Initializes a Movelist with a given size (Maybe just use MAX_NUMBER_MOVES)
 * @param moves MoveList Instance
 * @param size Number of Moves fit in the list
 */
void initMoveList( MoveList * moves, uint32 count );

/**
 * @brief Wrapper for adding move to a movelist
 *        also increments count in MoveList
 * @param moves MoveList Instance
 * @param move Move to add
 * @param index Position where to store move
 */
void addMove( MoveList * moves, Move move, uint32 index );


#endif
