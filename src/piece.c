#include <piece.h>
#include <ctype.h>

/**
 * @brief Initializes Piece
 */
void initPiece( Piece * p_piece, char p_symbol, Square * p_square, Board * p_board ) {
    p_piece->symbol = p_symbol;
    p_piece->last_move = NULL;
    p_piece->board = p_board;
    p_piece->square = p_square;
    p_piece->color = getColorForPiece( p_piece );
}

/**
 * @brief Returns color for piece piece
 * @param piece Piece
 * @return color Piececolor
 */
PieceColor getColorForPiece( const Piece * p_piece ) {
    if ( p_piece == NULL ) return NONE;
    if ( isupper( p_piece->symbol ) != 0 ) return WHITE;
    else return BLACK; 
}

/**
 * @brief Get Piece from board with x and y
 * @param board Board
 * @param x X
 * @param y Y
 * @return piece Piece
 */
Piece * getPiece( const Board * p_board, uint32 p_x, uint32 p_y ) {
    return p_board->squares[p_y][p_x].piece;
}

/**
 * @brief Checks if piece is piece_to_check
 * @param piece Piece to check with
 * @param piece_to_check Piece to check for
 * @return true if piece is piece_to_check
 */
bool isPiecePiece( const Piece * p_piece, Pieces p_piece_to_check ) {
    if ( p_piece == NULL ) return false;
    return ( toupper( p_piece->symbol ) == (int)p_piece_to_check );
}

/**
 * @brief Returns if char is symbol of a piece
 * @param p Char to check
 * @return true, if is piece, otherwise false
 */
bool isPiece( ColoredPiece p ) {
    return ( p == WHITE_PAWN   || p == BLACK_PAWN
          || p == WHITE_KNIGHT || p == BLACK_KNIGHT
          || p == WHITE_BISHOP || p == BLACK_BISHOP
          || p == WHITE_ROOK   || p == BLACK_ROOK
          || p == WHITE_QUEEN  || p == BLACK_QUEEN
          || p == WHITE_KING   || p == BLACK_KING );
}
