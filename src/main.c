#include <stdio.h>
#include <tdef.h>
#include <consoleio.h>

#include <board.h>
#include <move.h>
#include <logic.h>
#include <string.h>

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

    printf( "Line:%d\n", __LINE__ );
    // Get legal moves
    MoveNode * legal_moves = getLegalsPawn( board.squares[6][2].piece );

    printf( "Line:%d\n", __LINE__ );
   
    // Move
    // applyMoveBoard( &board, getMove( legal_moves, 0 ) );
    printBoard( &board, false );

    debugPrintMoveList( legal_moves );
    
    // Free memory
    clearMoveList( legal_moves, true );
    return 0;
}
