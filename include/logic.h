#ifndef __LOGIC__
#define __LOGIC__

#include <board.h>
#include <move.h>

#include <tdef.h>

typedef struct s_MoveNode MoveNode;

typedef enum {
    LEFT = -1,
    NO_H_DIRECTION = 0,
    RIGHT = 1
} Horizontal_Direction;

typedef enum {
    UP = -1,
    NO_V_DIRECTION = 0,
    DOWN = 1
} Vertical_Direction;

/**
 * @brief Gets legal moves for piece on square. If no piece on square, returns an empty list
 * @param square Square to check for legal moves for
 */
MoveNode * getLegals( Square * square );

/**
 * @brief Returns all legal moves for pawn in current position
 * @param pawn Pawn to get legal moves for
 * @return legal_moves Legal Moves for pawn
 */
MoveNode * getLegalsPawn( const Piece * pawn );

/**
 * @brief Checks for normal Pawn moves forward, If there are legal moves, adds thems to move_list
 * @param move_list Movelist legal Moves get added to
 * @param board Board
 * @param square Square of Pawn to check for
 * @return true, if there was atleast 1 legal move found, otherwise false
 */
bool getLegalPawnMove( MoveNode * move_list, const Board * board, Square * square );

/**
 * @brief Returns a legal Pawn Capture for direction, if there is no legal pawn capture return NULL
 * @param move_list List of Moves to add legal Pawncapture
 * @param square Square of Pawn
 * @param direction Direction of Pawn capture, usually Left or Right
 * @return true, if there was a legal move, otherwise false
 */
bool getLegalPawnCapture( MoveNode * move_list, Square * square, Horizontal_Direction direction );

/**
 * @brief Checks for legal enpassants, if there is enpassant found, adds them to move_list
 * @param move_list Movelist to add enpassant to
 * @param square Square of Pawn to check for enpassant for
 * @param direction Direction of looking for capture
 */
bool getLegalPawnEnpassant( MoveNode * move_list, Square * square, Horizontal_Direction direction );

/**
 * @brief Can check for horizontal, vertical and diagonal movement (Bishop, Queen, Rook, King )
 * @param piece Piece to check for legal moves for
 * @param x_direction X Direction to check for legal moves
 * @param y_direction Y Direction to check for legal moves
 * @param range -1 if infinite
 */
MoveNode * getLegalsCommon( const Piece * piece, Horizontal_Direction x_direction, Vertical_Direction y_direction, int32 range );

/**
 * @brief Returns legal moves for Queen
 * @param queen Queenpiece
 * @return legal_moves for queen
 */
MoveNode * getLegalsQueen( Piece * queen );

/**
 * @brief Returns legal moves for King
 * @param king Queenpiece
 * @return legal_moves for king
 */
MoveNode * getLegalsKing( Piece * king );

/**
 * @brief Returns legal moves for Rook
 * @param rook Rookpiece
 * @return legal_moves for Rook
 */
MoveNode * getLegalsRook( Piece * rook );

/**
 * @brief Returns legal moves for Bishop
 * @param bishop Bishoppiece
 * @return legal_moves for Bishop
 */
MoveNode * getLegalsBishop( Piece * bishop );

/**
 * @brief Appends Move to movelist with starting square and destination square
 * @param move_list Movelist move should be added to
 * @param start_square Square piece is placed on before moving
 * @param dest_square Square piece is placed on after moving
 */
void appendMoveWithSquares( MoveNode * move_list, Square * start_square, Square * dest_square );

/**
 * @brief Adds move of moves_to_add to move_list
 * @param move_list MoveList Moves get added to
 * @param moves_to_add Moves to add to move_list
 */
void addMovesToMoveNode( MoveNode * move_list, MoveNode * moves_to_add );

/**
 * @brief Checks if square is not occupied by same colored piece
 * @param piece Piece to possibly move
 * @param dest_square Square to check for same colored piece
 * @param color_sensitive If false, returns false not minding dest_square piece color, otherwise minds piece_color
 * @return true, if square is free of same colored piece, otherwise false
 */
bool isSquareFree( const Piece * piece, const Square * dest_square, bool color_sensitive );

/**
 * @brief Returns if square has Enemy
 * @param color Color of allied Piece
 * @param dest_square Destination Square to check for enemy
 * @return true, if has enemy, otherwise false
 */
bool squareHasEnemy( PieceColor color, const Square * dest_square );

/**
 * @brief Returns if square has Piece of same color
 * @param color Color of allied Piece
 * @param dest_square Destination Square to check for samecolored piece
 * @return true, if has teammate, otherwise false
 */
bool squareHasMate( PieceColor color, const Square * dest_square );

#endif
