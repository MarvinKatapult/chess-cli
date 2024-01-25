#include <stdio.h>
#include <tdef.h>
#include <consoleio.h>

#include <board.h>
#include <move.h>
#include <logic.h>

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

    // Get legal moves
    MoveNode * legal_moves = getLegalsPawn( board.squares[1][0].piece );

    // Print found moves
    debugPrintMoveList( legal_moves );
   
    // Move
    applyMoveBoard( &board, getMove( legal_moves, 0 ) );
    printBoard( &board, false );

    printf( "Number of legal moves for this pawn is %d\n", countMoveNodes( legal_moves ) );
    
    // Free memory
    clearMoveList( legal_moves, true );
    return 0;
}
