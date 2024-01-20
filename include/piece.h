#ifndef __PIECE__
#define __PIECE__

// #include <board.h>
#include <move.h>

#include <tdef.h>
#include <stdlib.h>

typedef struct s_Board Board;
typedef struct s_Square Square;

typedef enum {
    NONE = 0,
    WHITE,
    BLACK
} PieceColors;

typedef struct s_Piece {
    char symbol;
    Move * last_move;
    Board * board;
    Square * square;
    PieceColors color;
} Piece;


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

/**
 * @brief Initializes Piece
 * @param piece Piece
 * @param board Board of Piece
 */
void initPiece( Piece * piece, Square * square, Board * board );

/**
 * @brief Returns color for piece piece
 * @param piece Piece
 * @return color Piececolor
 */
PieceColors getColorForPiece( const Piece * piece );

/**
 * @brief Returns if char is symbol of a piece
 * @param piece Char to check
 * @return true, if is piece, otherwise false
 */
bool isPiece( ColoredPieces piece );

#endif
