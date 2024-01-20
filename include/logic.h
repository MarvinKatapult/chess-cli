#ifndef __LOGIC__
#define __LOGIC__

#include <board.h>
#include <tdef.h>

/**
 * @brief Moves a Piece on Board with the common chess notation
 * @param board Board
 * @param move Move e.g. "exd5"
 * @return true, if move was legal
 */
bool movePieceWithNotation( Board * board, cstring move );

#endif
