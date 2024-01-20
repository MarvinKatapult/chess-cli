#include <board.h>

/**
 * @brief Initiatlizes the Board with an empty field
 * @param board Board
 */
void boardInit( Board * p_board ) {
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
            square->piece = 0L;
        }
    }
}

/**
 * @brief Sets the Chessboard from fenstring
 * @param board Board
 * @param fen_string Fenstring
 */
void fromString( Board * p_board, cstring p_fen_string ) {

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
            Square * square = &p_board->squares[y_index][x_index];
            initPiece( piece, square, p_board );
            piece->symbol = current_char;

            // Add Piece to square
            square->piece = piece;
            square_index++; 
            continue;
        } 
    }
}

/**
 * @brief Prints the chessboard to the screen
 * @param board Board
 */
void printBoard( Board * p_board, bool p_clear_screen ) {

    // Clear the screen
    if ( p_clear_screen ) c_clear();

    c_print( " --Chess Board--" );
    c_print( "\n-----------------\n" );
    // Print Boar
    for ( uint32 y = 0; y < COUNT_SQUARES_PER_ROW; y++ ) {
        for ( uint32 x = 0; x < COUNT_SQUARES_PER_ROW; x++ ) {
            if ( x == 0 ) c_print( "|" );

            Piece * piece = p_board->squares[y][x].piece;
            if ( piece != 0L ) c_print( "%c|", piece->symbol );
            else
                // Only print | if not on last Column
                c_print( " |" ); 
        }
        // At the end of line, do linebreak
        c_print( "\n-----------------\n" );
    }
}

/**
 * @brief Moves a Piece on Board with the common chess notation
 * @param board Board
 * @param move Move e.g. "exd5"
 * @return true, if move was legal
 */
bool movePieceWithNotation( Board * board, cstring move ) {

    // Getting first char
    char current_char = move[0];
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
    // Get Piece to move
    Square * start_square = &p_board->squares[p_y1][p_x1];
    Square * dest_square  = &p_board->squares[p_y2][p_x2];

    Piece * piece = start_square->piece;
    if ( piece == 0L ) return false;

    // Move Piece
    dest_square->piece = piece;
    start_square->piece = 0L;

    return true;
}
