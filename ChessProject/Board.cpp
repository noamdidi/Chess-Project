#include "Board.h"
#include "Piece.h"
#include "Empty.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"
#include <iostream>

#define LEN_OF_ROW 8
#define LEN_OF_COLUMN 8

std::vector<Tile*> CreateTiles(std::string locationStr); //uses the functions below to return a vector containing the locations given in the string format.
bool CheckIfValidLetter(char toCheck); //Checks if a letter represents a valid location.
int TranslateLetterToIndex(char letter); //Turns a given letter into an index (A = 0, B = 1, etc...)

Board::Board()
{
	this->_current_turn = 0;
	
	this->_pieces.resize(LEN_OF_ROW);
	for (int row = 0; row < LEN_OF_ROW; row++)
	{
		this->_pieces[row].resize(LEN_OF_COLUMN);
		for (int column = 0; column < LEN_OF_COLUMN; column++)
		{
			this->_pieces[row][column] = new Empty(this, row, column);
		}
	}
	// Placing Rooks
		// Black:
	delete(this->_pieces[7][0]);
	this->_pieces[7][0] = new Rook(this, 'B', 7, 0);
	delete(this->_pieces[7][7]);
	this->_pieces[7][7] = new Rook(this, 'B', 7, 7);
		// White:
	delete(this->_pieces[0][0]);
	this->_pieces[0][0] = new Rook(this, 'W', 0, 0);
	delete(this->_pieces[0][7]);
	this->_pieces[0][7] = new Rook(this, 'W', 0, 7);

	// Placing Knights
		// Black:
	delete(this->_pieces[7][1]);
	this->_pieces[7][1] = new Knight(this, 'B', 7, 1);
	delete(this->_pieces[7][6]);
	this->_pieces[7][6] = new Knight(this, 'B', 7, 6);
		// White:
	delete(this->_pieces[0][1]);
	this->_pieces[0][1] = new Knight(this, 'W', 0, 1);
	delete(this->_pieces[0][6]);
	this->_pieces[0][6] = new Knight(this, 'W', 0, 6);

	// Placing Bishops
		// Black:
	delete(this->_pieces[7][2]);
	this->_pieces[7][2] = new Bishop(this, 'B', 7, 2);
	delete(this->_pieces[7][5]);
	this->_pieces[7][5] = new Bishop(this, 'B', 7, 5);
		// White:
	delete(this->_pieces[0][2]);
	this->_pieces[0][2] = new Bishop(this, 'W', 0, 2);
	delete(this->_pieces[0][5]);
	this->_pieces[0][5] = new Bishop(this, 'W', 0, 5);

	// Placing Queens
		// Black:
	delete(this->_pieces[7][4]);
	this->_pieces[7][4] = new Queen(this, 'B', 7, 4);;
		// White:
	delete(this->_pieces[0][4]);
	this->_pieces[0][4] = new Queen(this, 'W', 0, 4);

	// Placing Kings
		// Black:
	delete(this->_pieces[7][3]);
	this->_BKing = new King(this, 'B', 7, 3);
	this->_pieces[7][3] = this->_BKing;
		// White:
	delete(this->_pieces[0][3]);
	this->_WKing = new King(this, 'W', 0, 3);
	this->_pieces[0][3] = this->_WKing;

	// Placing Pawns
		// Black & White:
	for (int col = 0; col < LEN_OF_COLUMN; col++)
	{
		// Black Pawns:
		delete(this->_pieces[6][col]);
		this->_pieces[6][col] = new Pawn(this, 'B', 6, col);
		// White Pawns:
		delete(this->_pieces[1][col]);
		this->_pieces[1][col] = new Pawn(this, 'W', 1, col);
	}

	/*
	this loop pushes all the black pieces from rows 0 and 1 into the black pieces vector
	and all the white pieces from rows 6 and 7 into the white pieces vector.
	*/
	for (int i = 0; i < LEN_OF_ROW; i++)
	{
		this->_blacks.push_back(this->_pieces[7][i]);
		this->_blacks.push_back(this->_pieces[6][i]);
		this->_whites.push_back(this->_pieces[1][i]);
		this->_whites.push_back(this->_pieces[0][i]);
	}
}

Board::Board(Board& other)
{
	for (int row = 0; row < LEN_OF_ROW; row++)
	{
		for (int column = 0; column < LEN_OF_COLUMN; column++)
		{
			this->_pieces[row][column] = other._pieces[row][column];
		}
	}
}

Board::~Board()
{
	for (int row = 0; row < LEN_OF_ROW; row++)
	{
		for (int column = 0; column < LEN_OF_COLUMN; column++)
		{
			delete(this->_pieces[row][column]);
		}
	}
	for (int i = 0; i < this->_blacks.size(); i++)
	{
		delete(this->_blacks[i]);
	}
	for (int i = 0; i < this->_whites.size(); i++)
	{
		delete(this->_whites[i]);
	}
	this->_blacks.clear();
	this->_blacks.clear();
}

std::vector<std::vector<Piece*>> Board::GetLayout()
{
	return this->_pieces;
}

int Board::GetTurn()
{
	return this->_current_turn;
}

Piece* Board::GetKing(bool choice)
{
	if (choice)
	{
		return this->_WKing;
	}
	return this->_BKing;
}

std::vector<Piece*> Board::GetVectorOfTeam(bool choice)
{
	if (choice)
	{
		return this->_whites;
	}
	return this->_blacks;
}

void Board::SetWhiteVector(std::vector<Piece*> other)
{
	this->_whites = other;
}

void Board::SetBlackVector(std::vector<Piece*> other)
{
	this->_blacks = other;
}

bool Board::IsOnBoard(Tile* location)
{
	return (location->GetColumn() < 8 && location->GetColumn() > -1 && location->GetRow() < 8 && location->GetRow() > -1);
}

char Board::Move(std::string data)
{
	std::vector<Tile*> myTiles = CreateTiles(data); //the 0 index is the source and the 1 index is the destination.

	if (myTiles.size() == 2 && IsOnBoard(myTiles[0]) && IsOnBoard(myTiles[1]))
	{
		Piece* src = this->_pieces[myTiles[0]->GetRow()][myTiles[0]->GetColumn()];
		Piece* dst = this->_pieces[myTiles[1]->GetRow()][myTiles[1]->GetColumn()];

		char answer = src->IsValidMove(myTiles[0], myTiles[1]);
		if(answer == '0' || answer == '1')
		{
			src->Played();
			Tile* srcLoc = new Tile(*src->GetLocation());
			Tile* dstLoc = new Tile(*dst->GetLocation());
			Piece* temp = new Empty(this, srcLoc->GetRow(), srcLoc->GetColumn());
			delete(dst);
			this->_pieces[dstLoc->GetRow()][dstLoc->GetColumn()] = src;
			this->_pieces[srcLoc->GetRow()][srcLoc->GetColumn()] = temp;
			src->SetLocation(dstLoc);

			if (this->_current_turn == 1)
			{
				this->_current_turn = 0;
			}
			else if (this->_current_turn == 0)
			{
				this->_current_turn = 1;
			}
		}
		return answer;
	}
}

void Board::PrintBoard()
{
	//system("cls");
	std::cout <<  "  |A|B|C|D|E|F|G|H|\n";
	std::cout << "-------------------\n";
	for (int row = 0; row < LEN_OF_ROW; row++)
	{
		std::cout <<"|" << row + 1 << "|";
		for (int column = 0; column < LEN_OF_COLUMN; column++)
		{
			std::cout << this->_pieces[row][column]->GetType() << " ";
		}
		printf("\n");
	}
	printf("\n");
}

char* Board::CreateBoardString()
{
	char toRet[66] = {};
	int index = 0;
	for (int row = 0; row < LEN_OF_ROW; row++)
	{
		for (int column = 0; column < LEN_OF_COLUMN; column++)
		{
			toRet[index] = this->_pieces[row][column]->GetTeam();
			index++;
		}
	}
	return toRet;
}

/*
NOTE: letters should be ONLY lower case.
*/
std::vector<Tile*> CreateTiles(std::string locationStr)
{
	std::vector<Tile*> toRet;
	if (locationStr.length() == 4)
	{
		std::string firstLocation = locationStr.substr(0, 2);
		std::string secondLocation = locationStr.substr(2, 2);

		if ((int)firstLocation[1] < 57 && (int)firstLocation[1] > 48 && (int)secondLocation[1] < 57 || (int)secondLocation[1] > 48)
		{
			if (CheckIfValidLetter(firstLocation[0]) && CheckIfValidLetter(secondLocation[0]))
			{
				//The number value is the Row and the letter value is the Column.
				Tile* src = new Tile(((int)firstLocation[1] - 49), TranslateLetterToIndex(firstLocation[0])); //the char value minus 69 is the index in the array.
				Tile* dst = new Tile(((int)secondLocation[1] - 49), TranslateLetterToIndex(secondLocation[0])); //('1' char is 49)
				toRet.push_back(src);
				toRet.push_back(dst);
			}
		}
	}
	return toRet;
}

bool CheckIfValidLetter(char toCheck)
{
	char letters[LEN_OF_ROW] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
	for (int i = 0; i < LEN_OF_ROW; i++)
	{
		if (toCheck == letters[i])
		{
			return true;
		}
	}
	return false;
}

int TranslateLetterToIndex(char letter)
{
	char letters[LEN_OF_ROW] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
	for (int i = 0; i < LEN_OF_ROW; i++)
	{
		if (letter == letters[i])
		{
			return i;
		}
	}
}
