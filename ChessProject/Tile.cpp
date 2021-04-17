#include "Tile.h"

Tile::Tile(const int row, const int column)
{
	if (column > -1 && column < 8 && row > -1 && row < 8)
	{
		this->_column = column;
		this->_row = row;
	}
	else
	{
		this->_row = row;
		this->_column = column;
	}
}

Tile::Tile(Tile& other)
{
	this->_column = other.GetColumn();
	this->_row = other.GetRow();
}

Tile::~Tile()
{
}

int Tile::GetRow(void)
{
	return this->_row;
}

int Tile::GetColumn(void)
{
	return this->_column;
}

void Tile::SetRow(int newRow)
{
	this->_row = newRow;
}

void Tile::SetColumn(int newColumn)
{
	this->_column = newColumn;
}


