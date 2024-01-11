
#include <stdio.h>
#include <board.h>
#include <tdef.h>
#include <consoleio.h>

int main( int argc, string_array argv ) {
    
    // TODO Pass fenstring as Argument with --fen or -f
    
    char * board_string;
    // If no starting postition is passed, use default starting position
    if ( argc < 2 ) board_string = STARTING_FEN_STRING;
    else board_string = argv[1];

    // Create Board
    Board board;
    boardInit( &board );
    fromString( &board, board_string );

    return 0;
}
