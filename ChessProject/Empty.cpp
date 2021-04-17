#include "Empty.h"


Empty::Empty()
{
	this->_board = nullptr;
	this->_position = nullptr;
	this->_team = ' ';
	this->_type = ' ';
}

Empty::Empty(Board* board, const int row, const int column)
{
	this->_board = board;
	this->_position = new Tile(row, column);
	this->_team = 'N';
	this->_type = '#';
}

Empty::~Empty()
{
}

char Empty::IsValidMove(Tile* src, Tile* dst)
{
	return '2';
}

bool Empty::canIMoveLikeThis(Tile* dst)
{
	return false;
}
