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

    // Print moves
    // debugPrintMoveList( legal_moves );

    for ( int32 y = 0; y < COUNT_SQUARES_PER_ROW; y++ ) {
        for ( int32 x = 0; x < COUNT_SQUARES_PER_ROW; x++ ) {
            MoveNode * legal_moves = getLegals( &board.squares[y][x] );

            debugPrintBoard( &board, legal_moves );

            clearMoveList( legal_moves, true );
        }
    
    }

    // printBoard( &board, false, false );

    return 0;
}
