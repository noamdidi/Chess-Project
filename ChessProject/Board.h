#pragma once
#include "Piece.h"
#include <iostream>
#include <vector>


#define LEN_OF_ROW 8
#define LEN_OF_COLUMN 8

//To avoid repetitive inclusion.
class Piece; 
class Tile;

class Board
{
private:
	std::vector<std::vector<Piece*>> _pieces; //The board is a two dimentional array of pieces.
	int _current_turn; //0 for white, 1 for black.

	//Keeping the pointers for the kings of both teams would help verify if there is a "check".
	Piece* _BKing;
	Piece* _WKing;

	std::vector<Piece*> _whites; //vector containing all the living pieces of the white team.
	std::vector<Piece*> _blacks; //vector containing all the living pieces of the black team.
	 
public:
	Board(); //will input the default piece arrangement into the board.
	Board(Board& other);
	~Board();

	//Getters and Setters:
	std::vector<std::vector<Piece*>> GetLayout();
	int GetTurn();
	Piece* GetKing(bool choice); // true for white king, false for black.
	std::vector<Piece*> GetVectorOfTeam(bool choice); // true for white team, false for black.
	void SetWhiteVector(std::vector<Piece*> other);
	void SetBlackVector(std::vector<Piece*> other);

	//Checks if the given location has valid indexes.
	bool IsOnBoard(Tile* location);

	/*
	This function recievs a 4 character long string which has to be in the format of "letter + number + letter + number"
	which represent locations on the chess board. 
	(each number has to be between 1 - 8 and each letter has to be between a - h).
	it returns the corresponding response to the front end based on the given data.
	*/
	char Move(std::string data);
	
	// Print The Board!
	void PrintBoard();
	char* CreateBoardString();
};