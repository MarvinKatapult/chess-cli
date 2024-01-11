#include <board.h>

/**
 * @brief Initiatlizes the Board
 * @param board Board
 */
void boardInit( Board * p_board ) {
    for ( int y = 0; y < COUNT_BOARD_SQUARES / 9; y++ ) {
        for ( int x = 0; x < COUNT_BOARD_SQUARES / 9; x++ ) {
            int index = x + y * 9;
            Square * square = p_board->squares + index;

            // Set Color for Squares in Board
            if ( index % 2 == 0 ) square->color = WHITE_SQUARE;
            else square->color = BLACK_SQUARE;

            // Set x and y position
            square->x = x;
            square->y = y;
        }
    }
}
