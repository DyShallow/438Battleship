#include "MyForm.h"
#include <iostream>
#include <fstream>
#include "msclr\marshal_cppstd.h"

using namespace System;
using namespace System::Windows::Forms;
//using namespace std; // don't uncomment, causes problems

const int MAX_BOARD_SIZE = 20;
bool somethingWentWrong = false;
int player1HP = 0;
int player2HP = 0;
void update(Control^ control, int x, int y, int player);




class Ship {
public: short length; // length of ship, how far it goes from point of origin
		short width; // width of ship, does it bleed into adjacent spaces, only 1 allowed so far
		short xCoord; // point of origin
		short yCoord; // point of origin
		short orientation; // 1 = west, 2 = north, 3 = east, 4 = south. If a ship has width>1, even widths will protrude east/south
		short hp; // how many hits left to sunk. by default initialized to width*length

		Ship(short l, short w, short x, short y, short or ) {
			length = l;
			if (w != 1) { std::cout << "width is only allowed to be 1" << std::endl; }
			width = 1;
			xCoord = x;
			yCoord = y;
			orientation = or ;
			hp = length * width;
		}
};
struct Space {
	bool revealed; // revealed upon the opponent guessing this space
	bool shipPresent; // ship is present in this tile
	Ship* ship;
};
class Board {
public:
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
	MessageBox::Show("before for");
	for (int i = 0; i < sizeof(ships)/sizeof(&ships); i++) // for loop working? ffs - how to loop over array in cpp
	{
		MessageBox::Show("in for");
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
					MessageBox::Show("placing that ship");
				}
				break;
			default:
				MessageBox::Show("you shouldn't be here");
			}
		}
	}

}


};

Board* player1Board;


[STAThread]
void Main(array<String^, 1>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Ship shipArr[1] = { Ship(3,1,1,1,4) };
	player1Board = new Board(10, shipArr, 1);

	CppWinForm1::MyForm form;
	Application::Run(%form);



}

void buttonClicked(Control^ control, int x, int y, int player) {
	String^ managedString = "Player " + player + " Button at " + x + ", " + y + " pressed";

	// convert managed string to std::string
	//msclr::interop::marshal_context context;
	//std::string standardString = context.marshal_as<std::string>(managedString);

	// write to file
	//std::ofstream log;
	//log.open("log.txt");
	//log << standardString;
	//log.close();

	update(control, x, y, player);


	MessageBox::Show(managedString); // also useful for debugging woo!

}

int getXFromCoordString(String^ coordString) {
	int yIndex = coordString->IndexOf("y");
	String^ substr = coordString->Substring(1, yIndex - 1);
	int xCoord = Convert::ToInt32(substr);
	return xCoord;
}

int getYFromCoordString(String^ coordString) {
	int yIndex = coordString->IndexOf("y");
	String^ substr = coordString->Substring(yIndex + 1, coordString->Length - yIndex - 1);
	int yCoord = Convert::ToInt32(substr);
	return yCoord;
}

// update button appearance
void update(Control^ control, int x, int y, int player) {
	if (x < player1Board->dimension && y < player1Board->dimension) {
		if (player == 1) {
			player1Board->getSpace(x, y)->revealed = true;
			if (player1Board->getSpace(x, y)->shipPresent) {
				// hit
					// display hit
				control->BackColor = System::Drawing::Color::Red;
				// handle hit
					// decrement ship hp
					// check for sunk
						// check for endgame
			}
			else {
				// miss
				control->BackColor = System::Drawing::Color::White;
				// display miss
			}
		}
		else {
			// player 2, rpt above
		}
	}
	else {
		control->Enabled = false;
	}
}

void initialize() {
	// get path for config file or user settings
	// size of board
	// number/ type of ships


	// get path for placement file or player 1 placement (call player 1 exe in placement mode?)
	// check ships don't go out of bounds

	//Board playerOneBoard = new Board(, );

	// get path for placement file or player 2 placement (call player 2 exe in placement mode?)
	// check for out of bounds ships

	//Board playerTwoBoard = new Board( , );

	// initialize board with settings and placements (two boards)



}

void play() {
	//do
	// call player1 exe

	// get player1 move

	// check for legality

	// play move, reveal space, apply hp (if hit)

	// check for endgame condition

	// call player2 exe

	// get player2 move

	// check for legality

	// play move, reveal space, apply hp (if hit)

	// check for endgame condition
	//while(true)
}

void callEXE() {}

void getSettings() {}
void getPlacement() {}

// this function will set a ship s to board b.
// I know this is already in the constructor, but I wrote this just in case.  Didn't take me very long.
void setShip(Ship s, Board b) {
	for (int i = 0; i < s.length; i++) {
		if (s.orientation == 2)
		{
			b.setSpace(s.xCoord - i, s.yCoord, false, true, &s);
		}
		else if (s.orientation == 4)
		{
			b.setSpace(s.xCoord + i, s.yCoord, false, true, &s);
		}
		else if (s.orientation == 3)
		{
			b.setSpace(s.xCoord, s.yCoord + i, false, true, &s);
		}
		else if (s.orientation == 1)
		{
			b.setSpace(s.xCoord, s.yCoord - i, false, true, &s);
		}
	}
}
void getMove() {}

bool checkMove(int x, int y, Board b) {
	return true;
}

void updateGUI() {}


// this function will check to make sure that the placement
// of ship s is valid on board b
// IMPORTANT:  this is currently set up to test one single ship.
// has not been tested yet.
// Basic code structure:  for loop to cycle through each ship space.
// outer if statement will check to see what direction it is facing.
// middle if statement will check to make sure that the ship fits on the board.
// inner if statement ensures that each space on the board is not already taken.
bool checkLocation(Ship s, Board b) {
	bool valid = true;  // this is set to true.  It may become false later down in the function.  This will be returned.
	Space* sp;

	// loop to search for other ships
	for (int i = 0; i <= s.length; i++)  // check each possible location of ship s.
	{
		if (s.orientation == 1) {  // if new ship orientation is west
								   // set bounds according to ship size
			if ((s.xCoord - s.length) >= -1)
			{
				sp = b.getSpace(s.xCoord - i, s.yCoord);
				// to see if other ships located above starting position
				if (sp->shipPresent)
				{
					valid = false;
				}
			}
			else
			{
				valid = false;
			}
		}
		if (s.orientation == 2) {  // if new ship orientation is north
								   // set bounds according to ship size
			if ((s.yCoord - s.length) >= -1)
			{
				sp = b.getSpace(s.xCoord, s.yCoord - i);
				// to see if other ships located above starting position
				if (sp->shipPresent)
				{
					valid = false;
				}
			}
			else
			{
				valid = false;
			}
		}
		if (s.orientation == 3) {  // if new ship orientation is east
								   // set bounds according to ship size
			if ((s.xCoord - s.length) <= b.dimension)
			{
				sp = b.getSpace(s.xCoord + i, s.yCoord);
				// to see if other ships located above starting position
				if (sp->shipPresent)
				{
					valid = false;
				}
			}
			else
			{
				valid = false;
			}
		}
		if (s.orientation == 4) {  // if new ship orientation is south
								   // set bounds according to ship size
			if ((s.yCoord - s.length) <= b.dimension)
			{
				sp = b.getSpace(s.xCoord, s.yCoord + i);
				// to see if other ships located above starting position
				if (sp->shipPresent)
				{
					valid = false;
				}
			}
			else
			{
				valid = false;
			}
		}
	}
	return valid;
}

// simple game function to take care of a single move
bool doMove(int x, int y, Board b) {
	Space* sp = b.getSpace(x, y);
	if (sp->revealed == false) {  // is it a valid move?
		if (sp->shipPresent) {    // is there a ship there?
			sp->ship->hp--;       // decrement hp
		}
		sp->revealed = true;      // to show it has been guessed already
		return true;
	}
	else {
		return false;
	}
	updateGUI();
}

// simple function to determine if someone won.  It looks at the hp of each ship.
bool isGameOver(Ship ships[]) {
	bool over = true;
	for (int i = 0; i < sizeof(ships) / sizeof(ships[0]); i++) {  // carefully double check this condition here, I am not sure if this is the correct way to go through each one.
		if (ships[i].hp > 0) {
			over = false;
		}
	}
	return over;
}
void endGame() {

}

System::Void CppWinForm1::MyForm::player1Button_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	{
		Control^ senderControl = dynamic_cast<Control^>(sender);
		String^ coordString;
		if (senderControl != nullptr)
			coordString = dynamic_cast<String^>(senderControl->Tag);
		int x = getXFromCoordString(coordString);
		int y = getYFromCoordString(coordString);



		buttonClicked(senderControl, x, y, 1);
	}
}

System::Void CppWinForm1::MyForm::player2Button_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	Control^ senderControl = dynamic_cast<Control^>(sender);
	String^ coordString;
	if (senderControl != nullptr)
		coordString = dynamic_cast<String^>(senderControl->Tag);
	int x = getXFromCoordString(coordString);
	int y = getYFromCoordString(coordString);

	buttonClicked(senderControl, x, y, 2);
}
