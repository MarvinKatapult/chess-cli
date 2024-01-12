
#include <stdio.h>
#include <board.h>
#include <tdef.h>
#include <consoleio.h>

int main( int argc, string_array argv ) {
    
    // TODO Pass fenstring as Argument with --fen or -f
    
    string board_string;

    c_clear();

    // If no starting postition is passed, use default starting position
    if ( argc < 2 ) {
        c_print( "Please enter a fenstring:\n" );
        board_string = c_scan_string();
        c_clear();
    }
    else board_string = argv[1];

    // Create Board
    Board board;
    boardInit( &board );
    fromString( &board, board_string );

    c_print( "_______________\n" );
    string move = c_scan_string();

    c_clear();
    printBoard( &board );
    c_print( "_______________\n" );
    c_print( "You entered: %s\n", move );

    return 0;
}
