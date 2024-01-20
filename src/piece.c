#include <piece.h>
#include <ctype.h>

/**
 * @brief Initializes Piece
 */
void initPiece( Piece * p_piece, Square * p_square, Board * p_board ) {
    p_piece->symbol = ' ';
    p_piece->last_move = 0L;
    p_piece->board = p_board;
    p_piece->square = p_square;
    p_piece->color = getColorForPiece( p_piece );
}

/**
 * @brief Returns color for piece piece
 * @param piece Piece
 * @return color Piececolor
 */
PieceColors getColorForPiece( const Piece * p_piece ) {
    if ( p_piece == 0L ) return NONE;
    int symbol = p_piece->symbol;
    if ( islower( symbol ) > 0 ) return BLACK;
    else return WHITE; 
}

/**
 * @brief Returns if char is symbol of a piece
 * @param p Char to check
 * @return true, if is piece, otherwise false
 */
bool isPiece( ColoredPieces p ) {
    return ( p == WHITE_PAWN   || p == BLACK_PAWN
          || p == WHITE_KNIGHT || p == BLACK_KNIGHT
          || p == WHITE_BISHOP || p == BLACK_BISHOP
          || p == WHITE_ROOK   || p == BLACK_ROOK
          || p == WHITE_QUEEN  || p == BLACK_QUEEN
          || p == WHITE_KING   || p == BLACK_KING );
}
