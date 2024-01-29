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
   
    // Move to make enpassant legal
    Move double_pawn_move;
    initMove( &double_pawn_move, &board.squares[1][7], &board.squares[3][7] );

    applyMoveBoard( &board, &double_pawn_move );
    printBoard( &board, false );

    // Get legal moves
    MoveNode * legal_moves = getLegalsPawn( board.squares[3][6].piece );

    // Print moves
    debugPrintMoveList( legal_moves );
    
    // Free memory
    clearMoveList( legal_moves, true );

    return 0;
}
