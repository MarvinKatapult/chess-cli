#ifndef __PIECE__
#define __PIECE__

#include <board.h>
#include <move.h>

#include <tdef.h>
#include <stdlib.h>

#define WHITE_PAWN_START_ROW    6
#define BLACK_PAWN_START_ROW    1

typedef struct s_Board Board;
typedef struct s_Square Square;
typedef struct s_Move Move;

typedef enum {
    NO_COLOR = 0,
    WHITE,
    BLACK
} PieceColor;

typedef struct s_Piece {
    char symbol;
    Move * last_move;
    Board * board;
    Square * square;
    PieceColor color;
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
} ColoredPiece;

typedef enum {
    PAWN = 'P',
    KNIGHT = 'K',
    BISHOP = 'B',
    ROOK = 'R',
    QUEEN = 'Q',
    KING = 'K'
} Pieces;

/**
 * @brief Initializes Piece
 * @param piece Piece
 * @param board Board of Piece
 */
void initPiece( Piece * piece, char symbol, Square * square, Board * board );

/**
 * @brief Get Piece from board with x and y
 *        If the field is empty return 0L
 * @param board Board
 * @param x X
 * @param y Y
 * @return piece Piece
 */
Piece * getPiece( const Board * board, uint32 x, uint32 y );

/**
 * @brief Returns color for piece piece
 * @param piece Piece
 * @return color Piececolor
 */
PieceColor getColorForPiece( const Piece * piece );

/**
 * @brief Checks if piece is piece_to_check
 * @param piece Piece to check with
 * @param piece_to_check Piece to check for
 * @return true if piece is piece_to_check
 */
bool isPiecePiece( const Piece * piece, Pieces piece_to_check );

/**
 * @brief Returns if char is symbol of a piece
 * @param piece Char to check
 * @return true, if is piece, otherwise false
 */
bool isPiece( ColoredPiece piece );

#endif
