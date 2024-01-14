#ifndef __PIECE__
#define __PIECE__

#include <tdef.h>
#include <stdlib.h>

typedef enum {
    WHITE_PAWN   = 'P',
    WHITE_KNIGHT = 'N',
    WHITE_BISHOP = 'B',
    WHITE_ROOK   = 'R',
    WHITE_QUEEN  = 'Q',
    WHITE_KING   = 'K',

    BLACK_PAWN   = 'p',
    BLACK_KNIGHT = 'n',
    BLACK_BISHOP = 'b',
    BLACK_ROOK   = 'r',
    BLACK_QUEEN  = 'q',
    BLACK_KING   = 'k'
} ColoredPieces;

typedef enum {
    PAWN = 0,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
} Pieces;

typedef enum {
    WHITE = 0,
    BLACK
} PieceColors;

/**
 * @brief Returns if piece is same color as specified 
 * @param piece Piece
 * @param color Color
 * @return true, if piece is same color as color
 */
bool isPieceColor( char piece, PieceColors color );

/**
 * @brief Returns if char is symbol of a piece
 * @param piece Char to check
 * @return true, if is piece, otherwise false
 */
bool isPiece( ColoredPieces piece );

#endif
