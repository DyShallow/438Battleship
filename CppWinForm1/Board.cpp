#include "Ship.cpp"

#ifndef INCLUDED_MARSHAL
#define INCLUDED_MARSHAL
#include "msclr\marshal_cppstd.h"
#endif



struct Space {
	bool revealed; // revealed upon the opponent guessing this space
	bool shipPresent; // ship is present in this tile
	Ship* ship;
};


class Board {
public:
	const static int MAX_BOARD_SIZE = 20;
	bool somethingWentWrong = false;
	int dimension;
	int player; // 1 == player1, 2 == player2
	Space* getSpace(int x, int y) {
		if (x < dimension && y < dimension) {
			return board[x][y];
		}
		return NULL;
	}
	void setSpace(int x, int y, bool reveal, bool present, Ship* s) { // **************************************************** Made this
		if (x < dimension && y < dimension) {
			board[x][y]->revealed = reveal;
			board[x][y]->shipPresent = present;
			board[x][y]->ship = s;
		}
	}
private: Space* board[MAX_BOARD_SIZE][MAX_BOARD_SIZE]; // top left = (0,0)

public: Board(int dim, Ship ships[], int player) {
	if (dim > MAX_BOARD_SIZE) exit(-1); // invalid dim
	dimension = dim;
	this->player = player;
	for (int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			board[i][j] = new Space;
			board[i][j]->revealed = false;
			board[i][j]->shipPresent = false;
			if (this->player == 1) {

			}

		}
	}

	// note: check no ships are overlapping
	//System::Windows::Forms::MessageBox::Show("before for");
	for (int i = 0; i < sizeof(ships) / sizeof(&ships); i++) // for loop working? ffs - how to loop over array in cpp
	{
		//System::Windows::Forms::MessageBox::Show("in for");
		board[ships[i].xCoord][ships[i].yCoord]->shipPresent = true;
		board[ships[i].xCoord][ships[i].yCoord]->ship = &ships[i];
		if (ships[i].length > 1) {
			switch (ships[i].orientation) {
			case 1: // west

				for (int k = 1; k < ships[i].length; k++)
				{
					if (board[ships[i].xCoord - k][ships[i].yCoord]->shipPresent == true)somethingWentWrong = true; // if a ship is already here, overlapping ships!
					board[ships[i].xCoord - k][ships[i].yCoord]->shipPresent = true;
					board[ships[i].xCoord - k][ships[i].yCoord]->ship = &ships[i];
				}

				break;
			case 2: // north
				for (int k = 1; k < ships[i].length; k++)
				{
					if (board[ships[i].xCoord][ships[i].yCoord - k]->shipPresent == true)somethingWentWrong = true;
					board[ships[i].xCoord][ships[i].yCoord - k]->shipPresent = true;
					board[ships[i].xCoord][ships[i].yCoord - k]->ship = &ships[i];
				}
				break;
			case 3: // east
				for (int k = 1; k < ships[i].length; k++)
				{
					if (board[ships[i].xCoord + k][ships[i].yCoord]->shipPresent == true)somethingWentWrong = true;
					board[ships[i].xCoord + k][ships[i].yCoord]->shipPresent = true;
					board[ships[i].xCoord + k][ships[i].yCoord]->ship = &ships[i];
				}
				break;
			case 4: // south
				for (int k = 1; k < ships[i].length; k++)
				{
					if (board[ships[i].xCoord][ships[i].yCoord + k]->shipPresent == true)somethingWentWrong = true;
					board[ships[i].xCoord][ships[i].yCoord + k]->shipPresent = true;
					board[ships[i].xCoord][ships[i].yCoord + k]->ship = &ships[i];
					//System::Windows::Forms::MessageBox::Show("placing that ship");
				}
				break;
			default:
				System::Windows::Forms::MessageBox::Show("you shouldn't be here");
			}
		}
	}

}


};