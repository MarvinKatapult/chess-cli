
#include <stdio.h>
#include <board.h>
#include "tdef.h"
#include "consoleio.h"

int main( int argc, string_array argv ) {
    
    char * board_string;
    // If no starting postition is passed, use default starting position
    if ( argc < 2 ) board_string = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
    else board_string = argv[1];

    // Create Board
    struct Board board;
    boardInit( &board );
    //fromString( &board, board_string );

    return 0;
}
