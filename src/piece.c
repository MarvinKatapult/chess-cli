#include <piece.h>

/**
 * @brief Initializes Piece
 */
void initPiece( Piece * p_piece, Square * p_square, Board * p_board ) {
    p_piece->symbol = ' ';
    p_piece->last_move = 0L;
    p_piece->board = p_board;
    p_piece->square = p_square;
}

/**
 * @brief Returns if piece is same color as specified 
 * @param piece Piece
 * @param color Color
 * @return true, if piece is same color as color
 */
bool isPieceColor( char p, PieceColors p_color ) {
    if ( p_color == WHITE ) {
        return ( p == WHITE_PAWN   || p == WHITE_KNIGHT
            || p == WHITE_BISHOP || p == WHITE_ROOK
            || p == WHITE_QUEEN  || p == WHITE_KING );
    } else if ( p_color == BLACK ) {
        return ( p == BLACK_PAWN   || p == BLACK_KNIGHT
            || p == BLACK_BISHOP || p == BLACK_ROOK
            || p == BLACK_QUEEN  || p == BLACK_KING );
    }

    return false;
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
