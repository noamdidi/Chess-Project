#include "Knight.h"
#include "King.h"
#include <iostream>

Knight::Knight()
{
	this->_board = nullptr;
	this->_position = nullptr;
	this->_team = ' ';
	this->_type = ' ';
}

Knight::Knight(Board* board, const char team, const int row, const int column)
{
	this->_position = new Tile(row, column);

	if (board) //check if board is not null.
	{
		this->_board = board;
	}
	else
	{
		std::cout << "\n********\nBoard Cannot be NULL!\n********\n";
	}

	if (team == 'B') //check if team is valid.
	{
		this->_team = team;
		this->_type = 'n';
	}
	else if (team == 'W')
	{
		this->_team = team;
		this->_type = 'N';
	}
	else
	{
		std::cout << "\n********\nUnable to assign given team!\n********\n";
	}
}

Knight::~Knight()
{
}

char Knight::IsValidMove(Tile* src, Tile* dst)
{
	/*******************************************************************\
	|Check if src has a current player's piece before jumping into here.|
	|                    Should be done at Board.                       |
	\*******************************************************************/

	if (this->_board->GetTurn() == 0 && ((this->_board)->GetLayout())[src->GetRow()][src->GetColumn()]->GetTeam() != 'W' || this->_board->GetTurn() == 1 && this->_board->GetLayout()[src->GetRow()][src->GetColumn()]->GetTeam() != 'B')
	{
		return '2'; //Check if on the Piece on the given position is a Piece of the Current Player.
	}
	else if ((!this->_board->IsOnBoard(src)) || (!this->_board->IsOnBoard(dst)))
	{
		return '5'; //Check if src and dst is on the board.
	}
	else if (!this->canIMoveLikeThis(dst))
	{
		return '6'; //Check if the requested move is valid for the knight. 
	}
	else if (dst->GetColumn() == src->GetColumn() && dst->GetRow() == src->GetRow())
	{
		return '7'; //Check if dst is the same as src.
	}
	else if (this->_board->GetLayout()[dst->GetRow()][dst->GetColumn()]->GetTeam() == this->_team)
	{
		return '3'; //Check if on dst there is a piece from the same team as the player's team.
	}

	//This is to move the Piece and see if it causes check on the current player's king or on the oponent's.
	Tile* old_position = src;
	this->_position = new Tile(*dst);

	if (this->_team == 'W')
	{
		if (((King*)(this->_board->GetKing(true)))->IsThereCheckOnMe())//Check if the current move caused check on the current player's king.
		{
			return '4';
		}
		else if (((King*)(this->_board->GetKing(false)))->IsThereCheckOnMe())
		{
			return '1';
		}
	}
	else if (this->_team == 'B')
	{
		if (((King*)(this->_board->GetKing(false)))->IsThereCheckOnMe())
		{
			return '4';
		}
		else if (((King*)(this->_board->GetKing(true)))->IsThereCheckOnMe())
		{
			return '1';
		}
	}

	delete(this->_position);
	this->_position = old_position;

	this->_isPlayedYet = true;
	Eat(dst);
	return '0'; //Valid move.


	//As a bonus, Add check mate.
}

bool Knight::canIMoveLikeThis(Tile* dst)
{
	return (((abs(dst->GetRow() - this->_position->GetRow()) == 2) && (abs(dst->GetColumn() - this->_position->GetColumn()) == 1)) || ((abs(dst->GetColumn() - this->_position->GetColumn()) == 2) && (abs(dst->GetRow() - this->_position->GetRow()) == 1)));
}
