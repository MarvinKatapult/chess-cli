#include <move.h>

/**
 * @brief Initializes a Movelist with a given size (Maybe just use MAX_NUMBER_MOVES)
 * @note This function allocates memory that needs to be freed with free MoveList->moves
 * @param moves MoveList Instance
 * @param size Number of Moves fit in the list
 */
void initMoveList( MoveList * p_moves, uint32 p_count ) {
    p_moves->moves = (Move *)malloc( sizeof( Move ) * p_count );
    p_moves->count_moves = 0;
}

/**
 * @brief Wrapper for adding move to a movelist
 *        also increments count in MoveList
 * @param moves MoveList Instance
 * @param move Move to add
 * @param index Position where to store move
 */
void addMove( MoveList * p_moves, Move p_move, uint32 p_index ) {
    p_moves->count_moves++;
    p_moves->moves[p_index] = p_move;
}

