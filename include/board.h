#ifndef __BOARD__
#define __BOARD__

#include <stdio.h>
#include <square.h>

#define COUNT_BOARD_SQUARES     64

typedef struct s_Board {

    Square squares[64];    

} Board;

/**
 * @brief Initiates the Board
 * @param board Board
 */
void boardInit( Board * board );

/**
 * @brief Sets the Chessboard from fenstring
 * @param board Board
 * @param fen_string Fenstring
 */
void fromString( Board * board, const char * fen_string );

#endif
