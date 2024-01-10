
#include <stdio.h>

int main( int argv, char ** argc ) {
    
    char * board_string;
    // If no starting postition is passed, use default starting position
    if ( argv < 2 ) board_string = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
    else board_string = argc[1];

    printf( "Startboardstring: %s\n", board_string );

    return 0;
}
