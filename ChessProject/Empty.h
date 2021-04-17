#pragma once
#include "Board.h"

class Piece;
class Board;
class Tile;
class Empty : public Piece
{
public:
	Empty();
	Empty(Board* board, const int row, const int column);
	~Empty(); 

    virtual char IsValidMove(Tile* src, Tile* dst);
	virtual bool canIMoveLikeThis(Tile* dst);
};

