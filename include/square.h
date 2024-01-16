#ifndef __SQUARE__
#define __SQUARE__

#define WHITE_SQUARE   0
#define BLACK_SQUARE   1

typedef struct {
    char piece;
    unsigned int x;
    unsigned int y;
    unsigned int color;
} Square;

#endif
