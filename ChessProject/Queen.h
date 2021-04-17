#pragma once
#include "Board.h"

class Piece;
class Tile;
class Queen : public Piece
{
public:
	Queen();
	Queen(Board* board, const char team, const int row, const int column);
	~Queen(); //Will call the destructor of Piece.

	virtual char IsValidMove(Tile* src, Tile* dst);
	virtual bool canIMoveLikeThis(Tile* dst);
};

