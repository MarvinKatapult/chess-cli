
#include <logic.h>
#include <ctype.h>


/**
 * @brief Moves a Piece on Board with the common chess notation
 * @param board Board
 * @param move Move e.g. "exd5"
 * @return true, if move was legal
 */
bool movePieceWithNotation( Board * p_board, cstring p_move ) {

    // Getting first char
    char current_char = p_move[0];
    if ( current_char == '0' ) {
        // CASTLING
        // CHECK IF BIG OR SMALL CASTLE
    } else if ( IS_CHESS_COL( current_char ) ) {
        // PAWN MOVE OR PRECISION BECAUSE OF TWO OR MORE POSSIBLE MOVES

    } else if ( isdigit( current_char ) ) {
        // PRECISION BECAUSE OF TWO OR MORE POSSIBLE MOVES

    } else if ( isPiece( current_char ) ) {
        // PIECE MOVE 

    }

    // Couldnt Read String
    c_print( "Wrong format\n" );
    return false;
}

