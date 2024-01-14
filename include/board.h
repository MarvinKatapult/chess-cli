#ifndef __BOARD__
#define __BOARD__

#include <stdio.h>
#include <square.h>
#include <tdef.h>
#include <consoleio.h>

#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

#define COUNT_BOARD_SQUARES        64
#define COUNT_SQUARES_PER_ROW      8

#define STARTING_FEN_STRING        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"

// Checks if X is a-h
#define IS_CHESS_COL( X )  ( X >= 97 && X <= 104 )

typedef struct s_Board {

    Square squares[COUNT_SQUARES_PER_ROW][COUNT_SQUARES_PER_ROW];

} Board;

typedef enum {
    WHITE_PAWN = 'P',
    WHITE_KNIGHT = 'N',
    WHITE_BISHOP = 'B',
    WHITE_ROOK = 'R',
    WHITE_QUEEN = 'Q',
    WHITE_KING = 'K',

    BLACK_PAWN = 'p',
    BLACK_KNIGHT = 'n',
    BLACK_BISHOP = 'b',
    BLACK_ROOK = 'r',
    BLACK_QUEEN = 'q',
    BLACK_KING = 'k'
} Pieces;

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
 * @param clear_screen Clears the screen when set to true
 */
void printBoard( Board * board, bool clear_screen );

/**
 * @brief Moves a Piece on Board with the common chess notation
 * @param board Board
 * @param move Move e.g. "exd5"
 * @return true, if move was legal
 */
bool movePieceWithNotation( Board * board, cstring move );

/**
 * @brief Moves a Piece on Board from x1 and y1 to x2 and y2 (With no check for legality)
 * @param board Board
 * @param x1 X1
 * @param y1 Y1
 * @param x2 X2
 * @param y2 Y2
 * @return true, if move was legal
 */
bool movePieceNoCheck( Board * board, uint32 x1, uint32 y1, uint32 x2, uint32 y2 );

/**
 * @brief Returns if char is symbol of a piece
 * @param possible_piece Char to check
 * @return true, if is piece, otherwise false
 */
bool isPiece( char possible_piece );

#endif // __BOARD__
