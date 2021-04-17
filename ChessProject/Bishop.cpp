#include "Bishop.h"
#include "King.h"
#include <iostream>

Bishop::Bishop()
{
	this->_board = nullptr;
	this->_position = nullptr;
	this->_team = ' ';
	this->_type = ' ';
}

Bishop::Bishop(Board* board, const char team, const int row, const int column)
{
	this->_team = team;
	if (board) //check if board is not null.
	{
		this->_board = board;
	}
	else
	{
		std::cout << "\n********\nBoard Cannot be NULL!\n********\n";
	}
	this->_position = new Tile(row, column);
	if (this->_team == 'B')
	{
		this->_type = 'b';
	}
	else if (this->_team == 'W')
	{
		this->_type = 'B';
	}
	else
	{
		std::cout << "\n********\nUnable to assign given team!\n********\n";
	}
}

Bishop::~Bishop()
{
}

char Bishop::IsValidMove(Tile* src, Tile* dst)
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
		return '6'; //Check if the requested move is valid for the bishop. 
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


	// Checks if there are pieces in between the src and the dst
	int isBetween = 0;
	if (src->GetColumn() > dst->GetColumn())
	{
		if (src->GetRow() > dst->GetRow())
		{
			for (int row = src->GetRow() - 1, col = src->GetColumn() - 1; row > dst->GetRow(), col > dst->GetColumn(); row--, col--)
			{
				if (this->_board->GetLayout()[row][col]->GetType() != '#')
				{
					isBetween++;
				}
			}
		}
		else
		{
			for (int row = src->GetRow() + 1, col = src->GetColumn() - 1; row < dst->GetRow(), col > dst->GetColumn(); row++, col--)
			{
				if (this->_board->GetLayout()[row][col]->GetType() != '#')
				{
					isBetween++;
				}
			}
		}
	}
	else
	{
		if (src->GetRow() > dst->GetRow())
		{
			for (int row = src->GetRow() - 1, col = src->GetColumn() + 1; row > dst->GetRow(), col < dst->GetColumn(); row--, col++)
			{
				if (this->_board->GetLayout()[row][col]->GetType() != '#')
				if (this->_board->GetLayout()[row][col])
				{
					isBetween++;
				}
			}
		}
		else
		{
			for (int row = src->GetRow() + 1, col = src->GetColumn() + 1; row < dst->GetRow(), col < dst->GetColumn(); row++, col++)
			{
				if (this->_board->GetLayout()[row][col]->GetType() != '#')
				{
					isBetween++;
				}
			}
		}
	}

	if (!(isBetween))
	{
		this->_isPlayedYet = true;
		Eat(dst);
		return '0'; //Valid move.
	}
	else
	{
		return '6';
	}

	//As a bonus, Add check mate.
}

bool Bishop::canIMoveLikeThis(Tile* dst)
{
	return (abs(dst->GetRow() - this->_position->GetRow()) == abs(dst->GetColumn() - this->_position->GetColumn()));
}
