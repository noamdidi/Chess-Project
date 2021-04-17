#include "Piece.h"

Piece::Piece() : _board(nullptr), _position(nullptr), _team(' '), _type(' ')
{
}

Piece::Piece(Board* board) : _board(board) ,_position(new Tile(0,0)), _team('N'), _type('#')
{
}

Piece::Piece(Board* board, const char team, const char type, const int row, const int column)
{
	this->_board = board;
	this->_position->SetRow(row);
	this->_position->SetColumn(column);
	this->_type = type;
	if (team != 'N' && team != 'B' && team != 'W')
	{
		this->_team = 'N'; 
	}
	else
	{
		this->_team = team;
	}
}

Piece::Piece(Piece& other)
{
	this->_board = other._board;
	this->_position = other._position;
	this->_team = other._team;
	this->_type = other._type;
}

Piece::~Piece()
{
	delete(this->_position);
	//delete(this->_board);
}

Board* Piece::GetBoard()
{
	return this->_board;
}

char Piece::GetType()
{
	return this->_type;
}

char Piece::GetTeam()
{
	return this->_team;
}

Tile* Piece::GetLocation()
{
	return this->_position;
}

void Piece::Played()
{
	this->_isPlayedYet = true;
}

void Piece::SetLocation(Tile* newLocation)
{
	delete(this->_position);
	this->_position = new Tile(*newLocation);
}

void Piece::Eat(Tile* dst)
{
	if (this->_board->GetLayout()[dst->GetRow()][dst->GetColumn()]->GetType() != '#')
	{
		std::vector<Piece*> newVec;
		if (this->GetTeam() == 'B')
		{
			for (int i = 0; i < this->_board->GetVectorOfTeam(true).size(); i++)
			{
				if (this->_board->GetLayout()[dst->GetRow()][dst->GetColumn()] != this->_board->GetVectorOfTeam(true)[i])
				{
					newVec.push_back(this->_board->GetVectorOfTeam(true)[i]);
				}
			}
			this->_board->GetVectorOfTeam(true).clear();
			this->_board->SetWhiteVector(newVec);
		}
		if (this->GetTeam() == 'W')
		{
			for (int i = 0; i < this->_board->GetVectorOfTeam(false).size(); i++)
			{
				if (this->_board->GetLayout()[dst->GetRow()][dst->GetColumn()] != this->_board->GetVectorOfTeam(false)[i])
				{
					newVec.push_back(this->_board->GetVectorOfTeam(false)[i]);
				}
			}
			this->_board->GetVectorOfTeam(false).clear();
			this->_board->SetWhiteVector(newVec);
		}
	}
}
