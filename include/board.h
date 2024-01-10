#include <stdio.h>
#include <square.h>

#define COUNT_BOARD_SQUARES     64

struct Board {

    struct Square squares[64];    

};

/**
 * @brief Initiates the Board
 * @param board Board
 */
void boardInit( struct Board * board );

/**
 * @brief Sets the Chessboard from fenstring
 * @param board Board
 * @param fen_string Fenstring
 */
void fromString( struct Board * board, const char * fen_string );
