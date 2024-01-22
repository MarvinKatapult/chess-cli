#include <stdio.h>
#include <board.h>
#include <tdef.h>
#include <consoleio.h>

// TODO: Remove
bool printColor( Piece * p_piece ) {
    if ( p_piece != 0L ) {
        c_print( "Piece on square:%d;%d; is Color %s\n", p_piece->square->x, p_piece->square->y, p_piece->color == BLACK ? "Black" : "White" );
        return true;
    }
    c_print( "printColor: No piece on square\n" );
    return false;
}

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

    movePieceNoCheck( &board, 3, 6, 3, 4 );
    movePieceNoCheck( &board, 1, 7, 2, 5 );

    printBoard( &board, false );

    printColor( getPiece( &board, 2, 2 ) );
    printColor( getPiece( &board, 1, 1 ) );
    printColor( getPiece( &board, 2, 7 ) );
    printColor( getPiece( &board, 2, 7 ) );
    printColor( getPiece( &board, 3, 4 ) );
    printColor( getPiece( &board, 2, 6 ) );

    return 0;
}
