#pragma once
#include "Board.h"

class Piece;
class Tile;

class Knight : public Piece
{
public:
	Knight();
	Knight(Board* board, const char team, const int row, const int column);
	~Knight(); //Will call the destructor of Piece.

	virtual char IsValidMove(Tile* src, Tile* dst);
	virtual bool canIMoveLikeThis(Tile* dst);
};