#ifndef __SQUARE__
#define __SQUARE__

#include <piece.h>

#define WHITE_SQUARE   0
#define BLACK_SQUARE   1

typedef struct s_Square {
    struct s_Piece * piece;
    unsigned int x;
    unsigned int y;
    unsigned int color;
} Square;

#endif
