#include <logic.h>

#define GET_PAWN_Y_DIRECTION( X )   X->color == WHITE ? -1 : 1;

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

    // For convenience
    const Board * board = p_pawn->board; 
    Square * square = p_pawn->square; 

    // Create Movelist
    MoveNode * legal_moves = initMoveNode( NULL, NULL );

    // Check for normal Pawnmoves
    getLegalPawnMove( legal_moves, board, square );
    
    // Check for captures
    getLegalPawnCapture( legal_moves, square, LEFT );
    getLegalPawnCapture( legal_moves, square, RIGHT );

    // Check for enpassant
    getLegalPawnEnpassant( legal_moves, square, LEFT );
    getLegalPawnEnpassant( legal_moves, square, RIGHT );

    return legal_moves;
}

/**
 * @brief Checks for normal Pawn moves forward, If there are legal moves, adds thems to move_list
 * @param move_list Movelist legal Moves get added to
 * @param board Board
 * @param square Square of Pawn to check for
 * @return true, if there was atleast 1 legal move found, otherwise false
 */
bool getLegalPawnMove( MoveNode * p_move_list, const Board * p_board, Square * p_square ) {

    // Get Move direction
    Piece * pawn = p_square->piece;
    const int8 move_direction = GET_PAWN_Y_DIRECTION( pawn );

    // Check for one square move
    Square * dest_one_square = &p_board->squares[p_square->y + move_direction][p_square->x];
    bool can_move_one_square = false;
    if ( isSquareFree( pawn, dest_one_square, false ) ) {
        // Append new legal move
        appendMoveWithSquares( p_move_list, p_square, dest_one_square );
        can_move_one_square = true;
    }

    // Check for two square move
    bool pawn_on_starting_row = false;
    if ( pawn->color == WHITE ) pawn_on_starting_row = p_square->y == WHITE_PAWN_START_ROW;
    else                          pawn_on_starting_row = p_square->y == BLACK_PAWN_START_ROW;

    if ( !pawn_on_starting_row ) return can_move_one_square; 

    // Check for 2 square move
    Square * dest_two_square = &p_board->squares[p_square->y + move_direction * 2][p_square->x];
    bool can_move_two_squares = pawn_on_starting_row && isSquareFree( pawn, dest_two_square, false );
    if ( can_move_one_square && can_move_two_squares ) {
        appendMoveWithSquares( p_move_list, p_square, dest_two_square ); 
    }

    return can_move_two_squares;
}

/**
 * @brief Returns a legal Pawn Capture for direction, if there is no legal pawn capture return NULL
 * @param move_list List of Moves to add legal Pawncapture
 * @param square Square of Pawn
 * @param direction Direction of Pawn capture, usually Left or Right
 * @return true, if there was a legal move, otherwise false
 */
bool getLegalPawnCapture( MoveNode * p_move_list, Square * p_square, PawnCaptureDirection p_direction ) {
    // Get coordinates for destination p_square
    const int32 x_direction = p_direction == LEFT ? -1 : 1;
    const int32 y_direction = GET_PAWN_Y_DIRECTION( p_square->piece );
    const int32 x_coordinate = p_square->x + x_direction;
    const int32 y_coordinate = p_square->y + y_direction;

    // Check for edges of p_board
    if ( x_coordinate < 0 || x_coordinate > 7 ) return false;

    // Get destination p_square
    Board * board = p_square->piece->board;
    Square * dest_p_square = &board->squares[y_coordinate][x_coordinate];

    // Check if there is a an enemy piece on p_square
    bool ret = squareHasEnemy( p_square->piece->color, dest_p_square );
    if ( ret ) appendMoveWithSquares( p_move_list, p_square, dest_p_square );
    return ret;
}

/**
 * @brief Checks for legal enpassants, if there is enpassant found, adds them to move_list
 * @param move_list Movelist to add enpassant to
 * @param square Square of Pawn to check for enpassant for
 * @param direction Direction of looking for capture
 */
bool getLegalPawnEnpassant( MoveNode * p_move_list, Square * p_square, PawnCaptureDirection p_direction ) {
    const Board * board = p_square->board;
    const int32 y_direction = GET_PAWN_Y_DIRECTION( p_square->piece );
    // Get Squares
    Square * dest_square = &board->squares[p_square->y + y_direction][p_square->x + p_direction];
    Square * square_enemy_pawn = &board->squares[p_square->y][p_square->x + p_direction];

    // Get Pieces
    Piece * pawn = p_square->piece;
    Piece * enemy_pawn = square_enemy_pawn->piece;

    if ( enemy_pawn == NULL ) return false;

    // Check for enpassant
    if (    squareHasEnemy( pawn->color, square_enemy_pawn )
         && ( enemy_pawn->symbol == 'P' || enemy_pawn->symbol == 'p' )
         && enemy_pawn->last_move == board->last_move 
         && isSquareFree( pawn, dest_square, false ) ) {
         // Append Enpassant
         appendMoveWithSquares( p_move_list, p_square, dest_square );
         return true;
     }
    
     return false;
}

/**
 * @brief Appends Move to movelist with starting square and destination square
 * @param move_list Movelist move should be added to
 * @param start_square Square piece is placed on before moving
 * @param dest_square Square piece is placed on after moving
 */
void appendMoveWithSquares( MoveNode * p_move_list, Square * p_start_square, Square * p_dest_square ) {
    Move * new_legal_move = (Move *)malloc( sizeof( Move ) );
    initMove( new_legal_move, p_start_square, p_dest_square );
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
