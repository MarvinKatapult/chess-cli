#ifndef __MOVE__
#define __MOVE__

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
 * @note This function allocates memory that needs to be freed with free MoveList->moves
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
