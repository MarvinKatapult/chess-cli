#ifndef __BOARD__
#define __BOARD__

#include <stdio.h>
#include <square.h>
#include <tdef.h>
#include <consoleio.h>

#include <ctype.h>
#include <stdlib.h>

#define COUNT_BOARD_SQUARES        64
#define COUNT_SQUARES_PER_ROW      8

#define STARTING_FEN_STRING        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"

typedef struct s_Board {

    Square squares[COUNT_BOARD_SQUARES];

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
void fromString( Board * board, cstring fen_string );

/**
 * @brief Prints the chessboard to the screen
 * @param board Board
 */
void printBoard( Board * board );

#endif // __BOARD__
