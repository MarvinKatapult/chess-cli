#include <logic.h>

/**
 * @brief Returns all legal moves for pawn in current position
 * @param pawn Pawn to get legal moves for
 * @return legal_moves Legal Moves for pawn
 */
MoveNode * getLegalsPawn( const Piece * p_pawn ) {
    const Board * board = p_pawn->board; 
    const Square * square = p_pawn->square; 

    const int8 move_direction = getColorForPiece( p_pawn ) == WHITE ? -1 : 1;

    // Check for 1 square move
    MoveNode * legal_moves = initMoveNode( NULL, NULL );
    Square * dest_one_square = &board->squares[square->y + move_direction][square->x];
    bool can_move_one_square = false;
    if ( isSquareFree( p_pawn, dest_one_square, false ) ) {
        // Append new legal move
        appendMoveWithSquares( legal_moves, square, dest_one_square );
        can_move_one_square = true;
    }

    // Check for 2 square move
    // Check if pawn is on starting row
    bool pawn_on_starting_row = false;
    if ( p_pawn->color == WHITE ) pawn_on_starting_row = square->y == WHITE_PAWN_START_ROW;
    else                          pawn_on_starting_row = square->y == BLACK_PAWN_START_ROW;

    // Check for 2 square move
    Square * dest_two_square = &board->squares[square->y + move_direction * 2][square->x];
    if ( can_move_one_square && pawn_on_starting_row && isSquareFree( p_pawn, dest_two_square, false ) ) {
        appendMoveWithSquares( legal_moves, square, dest_two_square ); 
    }
    
    // Check for captures

    // Check for enpassant

    return legal_moves;
}

/**
 * @brief Appends Move to movelist with starting square and destination square
 * @param move_list Movelist move should be added to
 * @param start_square Square piece is placed on before moving
 * @param dest_square Square piece is placed on after moving
 */
void appendMoveWithSquares( MoveNode * p_move_list, const Square * p_start_square, const Square * p_dest_square ) {
    Move * new_legal_move = (Move *)malloc( sizeof( Move ) );
    initMove( new_legal_move, p_start_square->x, p_start_square->y, p_dest_square->x, p_dest_square->y, p_start_square->piece );
    appendMove( p_move_list, new_legal_move );
}

/**
 * @brief Checks if square is not occupied by same colored piece
 * @param piece Piece to possibly move
 * @param dest_square Square to check for same colored piece
 * @param color_sensitive If false, returns false not minding dest_square piece color, otherwise minds piece_color
 * @return true, if square is free of same colored piece, otherwise false
 */
bool isSquareFree( const Piece * p_piece, const Square * p_dest_square, bool p_color_sensitive ) {
    // Note: Has to be seperated to avoid segfault
    if ( p_dest_square->piece == NULL ) return true;
    if ( p_color_sensitive ) return ( p_dest_square->piece->color != p_piece->color );
    else return false;
}
