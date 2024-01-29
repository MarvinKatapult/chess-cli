#include <board.h>
#include <move.h>

/**
 * @brief Initiatlizes the Board with an empty field
 * @param board Board
 */
void boardInit( Board * p_board ) {

    // Allocate Memory
    p_board->squares = calloc( COUNT_SQUARES_PER_ROW, sizeof( Square * ) );
    for ( uint32 i = 0; i < COUNT_SQUARES_PER_ROW; i++ ) {
        p_board->squares[i] = calloc( COUNT_SQUARES_PER_ROW, sizeof( Square ) );
    }

    // Initialisation
    p_board->last_move = NULL;
    for ( uint32 y = 0; y < COUNT_SQUARES_PER_ROW; y++ ) {
        for ( uint32 x = 0; x < COUNT_SQUARES_PER_ROW; x++ ) {
            Square * square = &( p_board->squares[y][x] );

            // Set Color for Squares in Board
            uint32 index = x + y * COUNT_SQUARES_PER_ROW; 
            if ( index % 2 == 0 ) square->color = WHITE_SQUARE;
            else square->color = BLACK_SQUARE;

            // Set x and y position
            square->x = x;
            square->y = y;
            square->piece = NULL;
            square->board = p_board;
        }
    }
}

/**
 * @brief Sets the Chessboard from fenstring
 * @param board Board
 * @param fen_string Fenstring
 * @return true, if fenstring was set successfully, otherwise false
 */
bool setBoardFromString( Board * p_board, cstring p_fen_string ) {

    uint32 square_index = 0;
    uint32 char_index = 0; 
    char current_char = '0';

    // Go through fenstring
    while ( current_char != '\0' ) {
        current_char = p_fen_string[char_index++]; 

        // Skip / 
        if ( current_char == '/' )
            continue;

        // Calculate x and y of square
        uint32 x_index = square_index % COUNT_SQUARES_PER_ROW;
        uint32 y_index = square_index / COUNT_SQUARES_PER_ROW;

        // If Char is a number skip fields
        if ( isdigit( current_char ) ) {
            // Convert to number
            uint32 count_empty_fields = current_char - '0';
            square_index += count_empty_fields;
            continue;
        }

        // If current char is alpha read piece
        if ( isalpha( current_char ) ) {
            // Create New Piece
            Piece * piece = malloc( sizeof( Piece ) );

            // Check for out of bounds exception
            if ( square_index >= COUNT_BOARD_SQUARES ) return false;
            Square * square = &( p_board->squares[y_index][x_index] );
            initPiece( piece, current_char, square, p_board );

            // Add Piece to square
            square->piece = piece;
            square_index++; 
            continue;
        } 
    }

    return true;
}

/**
 * @brief Prints the chessboard to the screen
 * @param board Board
 */
void printBoard( Board * p_board, bool p_clear_screen ) {

    // Clear the screen
    if ( p_clear_screen ) c_clear();

    // Print Chessboard
    c_print( "    --Chess Board--\n" );
    c_print( "  -----------------\n" );
    for ( uint32 y = 0; y < COUNT_SQUARES_PER_ROW; y++ ) {
        for ( uint32 x = 0; x < COUNT_SQUARES_PER_ROW; x++ ) {
            if ( x == 0 ) c_print( "%d  |", y );

            Piece * piece = p_board->squares[y][x].piece;
            if ( piece != NULL ) c_print( "%c|", piece->symbol );
            else c_print( " |" ); 
        }
        // At the end of line, do linebreak
        c_print( "\n   -----------------\n" );
        if ( y == COUNT_SQUARES_PER_ROW - 1 ) c_print( "    0 1 2 3 4 5 6 7\n" );
    }
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
 * @brief Moves a Piece on Board from x1 and y1 to x2 and y2 (With no check for legality)
 * @param board Board
 * @param x1 X1
 * @param y1 Y1
 * @param x2 X2
 * @param y2 Y2
 * @return true, if move was successful
 */
bool movePieceNoCheck( Board * p_board, uint32 p_x1, uint32 p_y1, uint32 p_x2, uint32 p_y2 ) {
    // Get Squares
    Square * start_square = &( p_board->squares[p_y1][p_x1] );
    Square * dest_square  = &( p_board->squares[p_y2][p_x2] );

    // Get Piece
    Piece * piece = start_square->piece;
    if ( piece == NULL ) return false;

    // Move Piece
    dest_square->piece = piece;
    piece->square = dest_square;
    start_square->piece = NULL;

    return true;
}

/**
 * @brief Moves a piece on board with move
 * @param board Board
 * @param move Move for Board
 */
void applyMoveBoard( Board * p_board, Move * p_move ) {
    if ( p_move == NULL ) {
        c_print_err( "Move couldnt be applied to Board because move is null\n" );
        return;
    }
    // Get Squares
    Square * start_square = &p_board->squares[p_move->start_square->y][p_move->start_square->x];
    Square * dest_square = &p_board->squares[p_move->dest_square->y][p_move->dest_square->x];

    // Set Piece
    dest_square->piece = p_move->piece;
    start_square->piece = NULL;

    // Set Last move with piece
    p_move->piece->last_move = p_move;
    p_board->last_move = p_move;
}
