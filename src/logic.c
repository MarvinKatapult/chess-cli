#include <logic.h>

/**
 * @brief Returns all legal moves for pawn in current position
 * @param pawn Pawn to get legal moves for
 * @return legal_moves Legal Moves for pawn
 */
MoveNode * getLegalsPawn( const Piece * p_pawn ) {

    if ( p_pawn == NULL ) {
        c_print_err( "Recieved NULL Piece in getLegalIsPawn Line:%d; File:%s\n", __LINE__, __FILE__ );
        return NULL;
    }

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
    getLegalPawnCapture( legal_moves, board, square, LEFT );
    getLegalPawnCapture( legal_moves, board, square, RIGHT );

    // Check for enpassant

    return legal_moves;
}

/**
 * @brief Returns a legal Pawn Capture for direction, if there is no legal pawn capture return NULL
 * @param move_list List of Moves to add legal Pawncapture
 * @param board Board of Pawn
 * @param square Square of Pawn
 * @param direction Direction of Pawn capture, usually Left or Right
 * @return true, if there was a legal move, otherwise false
 */
bool getLegalPawnCapture( MoveNode * p_move_list, const Board * p_board, const Square * p_square, PawnCaptureDirection p_direction ) {
    // Get coordinates for destination p_square
    int32 x_p_direction = p_direction == LEFT ? -1 : 1;
    int32 y_p_direction = p_square->piece->color == WHITE ? -1 : 1;
    int32 x_coordinate = p_square->x + x_p_direction;
    int32 y_coordinate = p_square->y + y_p_direction;

    // Check for edges of p_board
    if ( x_coordinate < 0 || x_coordinate > 7 ) return false;

    // Get destination p_square
    Square * dest_p_square = &p_board->squares[y_coordinate][x_coordinate];

    // Check if there is a an enemy piece on p_square
    bool ret = squareHasEnemy( p_square->piece->color, dest_p_square );
    if ( ret ) appendMoveWithSquares( p_move_list, p_square, dest_p_square );
    return ret;
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

/**
 * @brief Returns if square has Enemy
 * @param color Color of allied Piece
 * @param dest_square Destination Square to check for enemy
 * @return true, if has enemy, otherwise false
 */
bool squareHasEnemy( PieceColor p_color, const Square * p_dest_square ) {
    if ( p_dest_square->piece == NULL ) return false;
    return ( p_dest_square->piece->color != p_color );
}
