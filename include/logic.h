#ifndef __LOGIC__
#define __LOGIC__

#include <board.h>
#include <piece.h>
#include <move.h>

#include <tdef.h>

/**
 * @brief Moves a Piece on Board with the common chess notation
 * @param board Board
 * @param move Move e.g. "exd5"
 * @return true, if move was legal
 */
bool movePieceWithNotation( Board * board, cstring move );

/**
 * @brief Initializes a Move
 * @param move Move
 * @param start_x Start X
 * @param start_y Start Y
 * @param dest_x Destination X
 * @param dest_y Destination Y
 * @param piece Piece to move
 */
void initMove( Move * move, uint32 start_x, uint32 start_y, uint32 dest_x, uint32 dest_y, Piece * piece ) {

}


#endif
