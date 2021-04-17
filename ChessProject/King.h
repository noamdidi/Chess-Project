#pragma once
#include "Board.h"

class Piece;
class Tile;

class King : public Piece
{
public:
	King();
	King(Board* board, const char team, const int row, const int column);
	~King(); //Will call the destructor of Piece.

	virtual char IsValidMove(Tile* src, Tile* dst);
	virtual bool canIMoveLikeThis(Tile* dst);
	bool IsThereCheckOnMe();
};