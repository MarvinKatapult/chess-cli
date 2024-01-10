
#include <board.h>

/**
 * @brief Initiatlizes the Board
 * @param board Board
 */
void boardInit( struct Board * p_board ) {
    for ( int y = 0; y < COUNT_BOARD_SQUARES / 9; y++ ) {
        for ( int x = 0; x < COUNT_BOARD_SQUARES / 9; x++ ) {
            int index = x + y * 9;
            struct Square * square = p_board->squares + index;

            // Set Color for Squares in Board
            if ( index % 2 == 0 ) square->color = WHITE_SQUARE;
            else square->color = BLACK_SQUARE;

            // Set x and y position
            square->x = x;
            square->y = y;
        }
    }
}

/**
 * @brief Sets the Chessboard from fenstring
 * @param board Board
 * @param fen_string Fenstring
 */
void fromString( struct Board * p_board, const char * p_fen_string ) {
    printf( "Fenstring: %s\n", p_fen_string );
}
