#pragma once
#include "Board.h"
#include "Tile.h"

class Board; //To avoid repetitive inclusion.
class Piece
{
protected:
	Board* _board; //The current Board.
	Tile* _position; // Row and Column (both integers).
	char _type; //If empty should be #, else (K/k = king, Q/q = queen, R/r = rook, P/p = pawn, N/n = knight, B/b = bishop) 
	//If char is upper case then team is White, lower case is Black..
	char _team; //B for Black Team, W for White Team, N for None.
	bool _isPlayedYet = false; //especially for pawn but can be used in castling implement
	

public:
	//There is no Default Constructor since we can not have a Piece without a Board. 
	//other parameters can be default values.
	Piece();
	Piece(Board* board); 
	Piece(Board* board, const char team, const char type, const int row, const int column);
	Piece(Piece& other); //Copy constructor.
	~Piece();

	// Getters & Setters
	Board* GetBoard();
	char GetType(); //empty - #, elsewise - (the corresponding letter of the piece)
	char GetTeam();
	Tile* GetLocation();
	void Played();
	void SetLocation(Tile* newLocation); //Should Be Checked if it is valid before sent here!
	void Eat(Tile* dst); //Checks if there is a piece on the dst and removes it from the team vector accordingly.

	virtual char IsValidMove(Tile* src, Tile* dst) = 0;
	virtual bool canIMoveLikeThis(Tile* dst) = 0;
};