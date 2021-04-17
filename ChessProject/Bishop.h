#pragma once
#include "Board.h"

class Piece;
class Tile;
class Bishop : public Piece
{
public:
	Bishop();
	Bishop(Board* board, const char team, const int row, const int column);
	~Bishop(); //Will call the destructor of Piece.

	virtual char IsValidMove(Tile* src, Tile* dst);
	virtual bool canIMoveLikeThis(Tile* dst);
};

