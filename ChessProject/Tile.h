#pragma once
class Tile
{
private:
	int _row;
	int _column;

public:
	//No default constructor because there can not be an uninitialized tile.
	Tile(const int row, const int column);
	Tile(Tile& other); //Copy constructor.
	~Tile();

	//Getters and Setters:
	int GetRow(void);
	int GetColumn(void);
	void SetRow(int newRow);
	void SetColumn(int newColumn);
};

