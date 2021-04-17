#pragma once
#include "Board.h"

class Piece;
class Tile;

class Pawn: public Piece
{
public:
	Pawn();
	Pawn(Board* board, const char team, const int row, const int column);
	~Pawn(); //Will call the destructor of Piece.

	virtual char IsValidMove(Tile* src, Tile* dst);
	virtual bool canIMoveLikeThis(Tile* dst);
};