#ifndef __LOGIC__
#define __LOGIC__

#include <board.h>
#include <move.h>

#include <tdef.h>

typedef struct s_MoveNode MoveNode;

/**
 * @brief Returns all legal moves for pawn in current position
 * @param pawn Pawn to get legal moves for
 * @return legal_moves Legal Moves for pawn
 */
MoveNode * getLegalsPawn( const Piece * pawn );

/**
 * @brief Appends Move to movelist with starting square and destination square
 * @param move_list Movelist move should be added to
 * @param start_square Square piece is placed on before moving
 * @param dest_square Square piece is placed on after moving
 */
void appendMoveWithSquares( MoveNode * move_list, const Square * start_square, const Square * dest_square );

/**
 * @brief Checks if square is not occupied by same colored piece
 * @param piece Piece to possibly move
 * @param dest_square Square to check for same colored piece
 * @param color_sensitive If false, returns false not minding dest_square piece color, otherwise minds piece_color
 * @return true, if square is free of same colored piece, otherwise false
 */
bool isSquareFree( const Piece * piece, const Square * dest_square, bool color_sensitive );

#endif
