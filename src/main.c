#include <tdef.h>
#include <consoleio.h>

#include <board.h>
#include <move.h>
#include <logic.h>

int main( int argc, string_array argv ) {
    
    // TODO Pass fenstring as Argument with --fen or -f
    string board_string;

    // If no starting postition is passed, use default starting position
    if ( argc < 2 ) board_string = DEFAULT_POSITION_FEN;
    else board_string = argv[1];

    // Create Board
    Board board;
    boardInit( &board );
    if ( !setBoardFromString( &board, board_string ) ) {
        c_print_err( "Couldnt Set Board with fenstring\n" );
        return 1;
    }

    getLegalsBoard( &board, true );

    c_print( "All done\n" );

    return 0;
}
