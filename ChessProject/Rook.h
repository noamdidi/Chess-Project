#pragma once
#include "Board.h"

class Piece;
class Tile;
class Rook : public Piece
{
public:
	Rook();
	Rook(Board* board, const char team, const int row, const int column);
	~Rook(); //Will call the destructor of Piece.

	virtual char IsValidMove(Tile* src, Tile* dst);
	virtual bool canIMoveLikeThis(Tile* dst);
};

