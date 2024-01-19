
#include <stdio.h>
#include <board.h>
#include <tdef.h>
#include <consoleio.h>

int main( int argc, string_array argv ) {
    
    // TODO Pass fenstring as Argument with --fen or -f
    string board_string;

    // If no starting postition is passed, use default starting position
    if ( argc < 2 ) {
        board_string = DEFAULT_POSITION_FEN;
    }
    else board_string = argv[1];

    // Create Board
    Board board;
    boardInit( &board );
    fromString( &board, board_string );

    printBoard( &board, false );

    movePieceNoCheck( &board, 3, 6, 3, 4 );
    movePieceNoCheck( &board, 1, 7, 2, 5 );

    printf( "\n\n" );

    printBoard( &board, false );

    return 0;
}
