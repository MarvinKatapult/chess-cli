#include <logic.h>
#include <stdlib.h>

#define GET_PAWN_Y_DIRECTION( X )   X->color == WHITE ? -1 : 1;
#define IS_COORDINATE_OUT_OF_BOUNDS( X )    ( X < 0 || X > 7 )

/**
 * @brief Returns all legal moves for pawn in current position
 * @param pawn Pawn to get legal moves for
 * @return legal_moves Legal Moves for pawn
 */
MoveNode * getLegalsPawn( const Piece * p_pawn ) {

    // Errorhandling
    if ( p_pawn == NULL || !isPiecePiece( p_pawn, PAWN ) ) {
        // c_print_err( "Recieved NULL Piece or non-pawn in getLegalIsPawn  Line:%d; File:%s\n", __LINE__, __FILE__ );
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
    else                        pawn_on_starting_row = p_square->y == BLACK_PAWN_START_ROW;

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
bool getLegalPawnCapture( MoveNode * p_move_list, Square * p_square, Horizontal_Direction p_direction ) {
    // Get coordinates for destination p_square
    const int32 x_direction = p_direction == LEFT ? -1 : 1;
    const int32 y_direction = GET_PAWN_Y_DIRECTION( p_square->piece );
    const int32 x_coordinate = p_square->x + x_direction;
    const int32 y_coordinate = p_square->y + y_direction;

    // Check for edges of p_board
    if ( IS_COORDINATE_OUT_OF_BOUNDS( x_coordinate ) ) return false;

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
bool getLegalPawnEnpassant( MoveNode * p_move_list, Square * p_square, Horizontal_Direction p_direction ) {
    const Board * board = p_square->board;
    const int32 y_direction = GET_PAWN_Y_DIRECTION( p_square->piece );
    // Get Squares
    const int32 x_coordinate = p_square->x + p_direction;
    const int32 y_coordinate = p_square->y + y_direction;
    if ( IS_COORDINATE_OUT_OF_BOUNDS( x_coordinate ) ) return false;

    Square * dest_square = &board->squares[y_coordinate][x_coordinate];
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
 * @brief Can check for horizontal, vertical and diagonal movement (Bishop, Queen, Rook, King )
 * @param piece Piece to check for legal moves for
 * @param x_direction X Direction to check for legal moves
 * @param y_direction Y Direction to check for legal moves
 * @param range -1 if infinite
 */
MoveNode * getLegalsCommon( const Piece * p_piece, Horizontal_Direction p_x_direction, Vertical_Direction p_y_direction, int32 p_range ) {
    MoveNode * legal_moves = initMoveNode( NULL, NULL );
    if ( p_piece == NULL ) {
        c_print_err( "getLegalsCommon recieved a NULL Piece Line:%d File:%s\n", __LINE__, __FILE__ );
        return legal_moves;
    }

    const Board * board = p_piece->board;
    Square * start_square = p_piece->square;

    bool reached_end = false;
    for ( int32 i = 1; !reached_end; i++ ) {
        // Return if range
        if ( i > p_range && p_range != -1 ) break;;
        const int32 y_coordinate = start_square->y + p_y_direction * i;
        const int32 x_coordinate = start_square->x + p_x_direction * i;

        // Check for x or y being out of bounds
        if ( IS_COORDINATE_OUT_OF_BOUNDS( x_coordinate ) || IS_COORDINATE_OUT_OF_BOUNDS( y_coordinate ) ) break;

        Square * dest_square = &board->squares[y_coordinate][x_coordinate];
        if ( squareHasEnemy( p_piece->color, dest_square ) ) {
            appendMoveWithSquares( legal_moves, start_square, dest_square );
            reached_end = true;
            break;
        }
        else if ( squareHasMate( p_piece->color, dest_square ) ) {
            reached_end = true;
            break;
        }
        else appendMoveWithSquares( legal_moves, start_square, dest_square );
    }

    return legal_moves;
}

/**
 * @brief Returns legal moves for Queen
 * @param queen Queenpiece
 * @return legal_moves for queen
 */
MoveNode * getLegalsQueen( Piece * p_queen ) {
    MoveNode * legal_queen_moves = initMoveNode( NULL, NULL );
    if ( p_queen == NULL ) {
        c_print_err( "Recieved NULL Piece in getLegalsQueen Line:%d File:%s\n", __LINE__, __FILE__ );
        return legal_queen_moves;
    }

    addMovesToMoveNode( legal_queen_moves, getLegalsCommon( p_queen, LEFT,           NO_V_DIRECTION, -1 ) );
    addMovesToMoveNode( legal_queen_moves, getLegalsCommon( p_queen, LEFT,           UP, -1 ) );
    addMovesToMoveNode( legal_queen_moves, getLegalsCommon( p_queen, NO_H_DIRECTION, UP, -1 ) );
    addMovesToMoveNode( legal_queen_moves, getLegalsCommon( p_queen, RIGHT,          UP, -1 ) );
    addMovesToMoveNode( legal_queen_moves, getLegalsCommon( p_queen, RIGHT,          NO_V_DIRECTION, -1 ) );
    addMovesToMoveNode( legal_queen_moves, getLegalsCommon( p_queen, RIGHT,          DOWN, -1 ) );
    addMovesToMoveNode( legal_queen_moves, getLegalsCommon( p_queen, NO_H_DIRECTION, DOWN, -1 ) );
    addMovesToMoveNode( legal_queen_moves, getLegalsCommon( p_queen, LEFT,           DOWN, -1 ) );
    return legal_queen_moves;
}

/**
 * @brief Returns legal moves for King
 * @param king Queenpiece
 * @return legal_moves for king
 */
MoveNode * getLegalsKing( Piece * p_king ) {
    MoveNode * legal_king_moves = initMoveNode( NULL, NULL );
    if ( p_king == NULL ) {
        c_print_err( "Recieved NULL Piece in getLegalsQueen Line:%d File:%s\n", __LINE__, __FILE__ );
        return legal_king_moves;
    }

    addMovesToMoveNode( legal_king_moves, getLegalsCommon( p_king, LEFT,           NO_V_DIRECTION, 1 ) );
    addMovesToMoveNode( legal_king_moves, getLegalsCommon( p_king, LEFT,           UP, 1 ) );
    addMovesToMoveNode( legal_king_moves, getLegalsCommon( p_king, NO_H_DIRECTION, UP, 1 ) );
    addMovesToMoveNode( legal_king_moves, getLegalsCommon( p_king, RIGHT,          UP, 1 ) );
    addMovesToMoveNode( legal_king_moves, getLegalsCommon( p_king, RIGHT,          NO_V_DIRECTION, 1 ) );
    addMovesToMoveNode( legal_king_moves, getLegalsCommon( p_king, RIGHT,          DOWN, 1 ) );
    addMovesToMoveNode( legal_king_moves, getLegalsCommon( p_king, NO_H_DIRECTION, DOWN, 1 ) );
    addMovesToMoveNode( legal_king_moves, getLegalsCommon( p_king, LEFT,           DOWN, 1 ) );
    return legal_king_moves;
}

/**
 * @brief Returns legal moves for Rook
 * @param rook Rookpiece
 * @return legal_moves for Rook
 */
MoveNode * getLegalsRook( Piece * p_rook ) {
    MoveNode * legal_rook_moves = initMoveNode( NULL, NULL );
    if ( p_rook == NULL ) {
        c_print_err( "Recieved NULL Piece in getLegalsRook Line:%d File:%s\n", __LINE__, __FILE__ );
        return legal_rook_moves;
    }
    addMovesToMoveNode( legal_rook_moves, getLegalsCommon( p_rook, LEFT,           NO_V_DIRECTION, -1 ) );
    addMovesToMoveNode( legal_rook_moves, getLegalsCommon( p_rook, RIGHT,          NO_V_DIRECTION, -1 ) );
    addMovesToMoveNode( legal_rook_moves, getLegalsCommon( p_rook, NO_H_DIRECTION, UP, -1 ) );
    addMovesToMoveNode( legal_rook_moves, getLegalsCommon( p_rook, NO_H_DIRECTION, DOWN, -1 ) );

    return legal_rook_moves;
}

/**
 * @brief Returns legal moves for Bishop
 * @param bishop Bishoppiece
 * @return legal_moves for Bishop
 */
MoveNode * getLegalsBishop( Piece * p_bishop ) {
    MoveNode * legal_bishop_moves = initMoveNode( NULL, NULL );
    if ( p_bishop == NULL ) {
        c_print_err( "Recieved NULL Piece in getLegalsBishop Line:%d File:%s\n", __LINE__, __FILE__ );
        return legal_bishop_moves;
    }
    addMovesToMoveNode( legal_bishop_moves, getLegalsCommon( p_bishop, LEFT,  UP, -1 ) );
    addMovesToMoveNode( legal_bishop_moves, getLegalsCommon( p_bishop, LEFT,  DOWN, -1 ) );
    addMovesToMoveNode( legal_bishop_moves, getLegalsCommon( p_bishop, RIGHT, UP, -1 ) );
    addMovesToMoveNode( legal_bishop_moves, getLegalsCommon( p_bishop, RIGHT, DOWN, -1 ) );

    return legal_bishop_moves;
}

/**
 * @brief Returns legal moves for Bishop
 * @param knight Knightpiece
 * @return legal_moves for knight
 */
MoveNode * getLegalsKnight( Piece * p_knight ) {
    MoveNode * legal_knight_moves = initMoveNode( NULL, NULL );
    if ( p_knight == NULL ) {
        c_print_err( "Recieved NULL Knight Piece in getLegalsKnight Line:%d File:%s\n", __LINE__, __FILE__ );
        return legal_knight_moves;
    }    

    Square * square = p_knight->square;
    Board * board = p_knight->board;

    for ( int32 x = -2; x <= 2; x++ ) {
        for ( int32 y = -2; y <= 2; y++ ) {
            // Get x and y
            int32 x_coordinate = square->x + x;
            int32 y_coordinate = square->y + y;

            // Check for outofbounds
            if ( IS_COORDINATE_OUT_OF_BOUNDS( y_coordinate ) || y == 0) continue;
            if ( IS_COORDINATE_OUT_OF_BOUNDS( x_coordinate ) || x == 0 ) break;
            if ( abs( x ) == abs( y ) ) continue;

            Square * dest_square = &board->squares[y_coordinate][x_coordinate];
            // Check for samecolored piece on square
            if ( !squareHasMate( p_knight->color, dest_square ) ) appendMoveWithSquares( legal_knight_moves, square, dest_square );
        }
    }

    return legal_knight_moves;
}

/**
 * @brief Returns a list of legal moves for every piece on board
 * @param board Board to check for legal moves for
 * @param print_board If true prints the board for every piece with legal moves
 * @return legal moves
 */
MoveNode * getLegalsBoard( Board * p_board, bool p_print_board ) {
    MoveNode * legal_moves = initMoveNode( NULL, NULL );
    if ( p_board == NULL ) {
        c_print_err( "Recieved NULL Board in getLegalsBoard Line:%s File:%s\n", __LINE__, __FILE__ );
        return legal_moves; 
    } 

    // Get Legals for every square
    for ( int32 y = 0; y < COUNT_SQUARES_PER_ROW; y++ ) {
        for ( int32 x = 0; x < COUNT_SQUARES_PER_ROW; x++ ) {
            MoveNode * legal_moves_for_piece = getLegalsSquare( &p_board->squares[y][x] );
            addMovesToMoveNode( legal_moves, legal_moves_for_piece );

            if ( p_print_board )debugPrintBoard( p_board, legal_moves_for_piece );
        }
    }

    return legal_moves;
}

/**
 * @brief Gets legal moves for piece on square. If no piece on square, returns an empty list
 * @param square Square to check for legal moves for
 */
MoveNode * getLegalsSquare( Square * p_square ) {
    MoveNode * legal_moves = initMoveNode( NULL, NULL );
    if ( p_square == NULL ) return legal_moves;

    Piece * piece = p_square->piece;
    if ( piece == NULL ) return legal_moves;

    switch ( piece->symbol ) {
        case WHITE_PAWN:
        case BLACK_PAWN:
            return getLegalsPawn( piece );
        case WHITE_ROOK:
        case BLACK_ROOK:
            return getLegalsRook( piece );
        case WHITE_BISHOP:
        case BLACK_BISHOP:
            return getLegalsBishop( piece );
        case WHITE_KNIGHT:
        case BLACK_KNIGHT:
            return getLegalsKnight( piece );
        case WHITE_QUEEN:
        case BLACK_QUEEN:
            return getLegalsQueen( piece );
        case WHITE_KING:
        case BLACK_KING:
            return getLegalsKing( piece );
        default:
            return legal_moves;
    }
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
 * @brief Adds move of moves_to_add to move_list
 * @param move_list MoveList Moves get added to
 * @param moves_to_add Moves to add to move_list
 */
void addMovesToMoveNode( MoveNode * p_move_list, MoveNode * p_moves_to_add ) {
    if ( p_move_list == NULL || p_moves_to_add == NULL ) return;

    MoveNode * current = p_moves_to_add;
    while ( current != NULL ) {
        // Check for null move
        if ( current->move == NULL ) {
            current = current->next;
            continue;
        }

        // Append move
        Move * move = current->move;
        appendMove( p_move_list, move );

        current = current->next;
    }
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

/**
 * @brief Returns if square has Piece of same color
 * @param color Color of allied Piece
 * @param dest_square Destination Square to check for samecolored piece
 * @return true, if has teammate, otherwise false
 */
bool squareHasMate( PieceColor p_color, const Square * p_dest_square ) {
    if ( p_dest_square->piece == NULL ) return false;
    return ( p_dest_square->piece->color == p_color );
}
