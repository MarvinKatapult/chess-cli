#include <board.h>

/**
 * @brief Initiatlizes the Board
 * @param board Board
 */
void boardInit( Board * p_board ) {
    for ( uint32 y = 0; y < COUNT_BOARD_SQUARES / 9; y++ ) {
        for ( uint32 x = 0; x < COUNT_BOARD_SQUARES / 9; x++ ) {
            const uint32 index = x + y * 9;
            Square * square = p_board->squares + index;

            // Set Color for Squares in Board
            if ( index % 2 == 0 ) square->color = WHITE_SQUARE;
            else square->color = BLACK_SQUARE;

            // Set x and y position
            square->x = x;
            square->y = y;

            square->piece = ' ';
        }
    }
}

/**
 * @brief Sets the Chessboard from fenstring
 * @param board Board
 * @param fen_string Fenstring
 */
void fromString( Board * p_board, cstring p_fen_string ) {

    // Go through fenstring
    uint32 square_index = 0;
    uint32 char_index = 0; 

    char current_char = '0';
    while ( current_char != '\0' ) {
        current_char = p_fen_string[char_index++]; 
        printf( "%c", current_char );

        // Skip / 
        if ( current_char == '/' )
            continue;

        // If Char is a number skip fields
        if ( isdigit( current_char ) ) {
            // Convert to number
            uint32 count_empty_fields = current_char - '0';
            square_index += count_empty_fields;
            continue;
        }

        // If current char is alpha read piece
        if ( isalpha( current_char ) ) {
            p_board->squares[square_index].piece = current_char;
            square_index++; 
            continue;
        } 
    }

    printBoard( p_board );
}

/**
 * @brief Prints the chessboard to the screen
 * @param board Board
 */
void printBoard( Board * p_board ) {

    // Clear the screen
    // c_clear();
    c_print( "\n" );

    // Print Board
    for ( uint32 i = 0; i < COUNT_BOARD_SQUARES; i++ ) {
        c_print( "%c ", p_board->squares[i].piece );
        // At the end of line, do linebreak
        if ( (i + 1) % 8 == 0 ) c_print( "\n" );
    }
}
