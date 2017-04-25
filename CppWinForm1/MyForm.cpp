#include "MyForm.h"
#ifndef INCLUDED_IOS
#define INCLUDED_IOS
#include <iostream>
#endif
#include <fstream>
#ifndef INCLUDED_MARSHAL
#define INCLUDED_MARSHAL
#include "msclr\marshal_cppstd.h"
#endif
#include "Board.cpp"

using namespace System;
using namespace System::Windows::Forms;
//using namespace std; // don't uncomment, causes problems

// variable declarations

int player1HP = 0;
int player2HP = 0;
Board* player1Board;
bool player1isHuman;
bool player2isHuman;
bool showPlayer1Console;
bool showPlayer2Console;
int timeLimit; // in seconds



// function declarations
void update(Control^ control, int x, int y, int player); // does a move
void illegalMove(int player); // player made an illegal move
void endGame(int winner); // player winner wins game
bool checkMoveLegality(int x,int y, Board* player1Board); // checks legality of move, true if legal, false if illegal
void buttonClicked(Control^ control, int x, int y, int player); // does actions after a move is manually input










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
			// check for legality
			if (checkMoveLegality(x,y, player1Board) == false) illegalMove(1);
			
			player1Board->getSpace(x, y)->revealed = true;
			if (player1Board->getSpace(x, y)->shipPresent) {
				// hit
				
					// display hit
				control->BackColor = System::Drawing::Color::Red;
				// handle hit
					// decrement ship hp
				int shipRemainingHP = player1Board->getSpace(x, y)->ship->hit(x, y); // returns remaining hp
					// decrement player hp
				player1HP = player1HP - 1;
				
				//array<Control ^, 1>^ player1HPLabelarr = control->Parent->Parent->player1HPLabel->Text = "Total Ship HP Remaining:  " + player1HP;
				//Label ^ player1HPLabel = dynamic_cast<Label^>(player1HPLabelarr[0]);
				//player1HPLabel->Text = 
					// check for sunk
				if (shipRemainingHP == 0) { // sunk
					
				}
				else {

				}
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
	//Ship ships1[];  // ********************************************************************************************* QUESTION HOW SHOULD I DECLARE MY SHIPS?
	//Ship ships2[];
	//int dimension;
	//Board *b1 = new Board(dimension, ships1);
	//Board *b2 = new Board(dimension, ships2);

	// get path for config file or user settings
	// size of board
	// number/ type of ships


	// get path for placement file or player 1 placement (call player 1 exe in placement mode?)


	// check for out of bounds ships
	//for (int i = 0; i < sizeof(ships1) / sizeof(ships1[0]); i++) {
	//	checkLocation(ships1[i], *b1);  // ****************************************************************** May want to change this to board pointer in function call
	//}


	// get path for placement file or player 2 placement (call player 2 exe in placement mode?)



	// check for out of bounds ships
	//for (int i = 0; i < sizeof(ships2) / sizeof(ships2[0]); i++) {
	//	checkLocation(ships2[i], *b2);  // ****************************************************************** May want to change this to board pointer in function call
	//}

	//Board playerTwoBoard = new Board( , );

	// initialize board with settings and placements (two boards)



}

void play(Board b1, Board b2, Ship player1Ships[], Ship player2Ships[]) {
	//int x; // x coordinate
	//int y; // y coordinate
	//do {
	//	// call player1 exe

	//	// get player1 move
	//	//x = getX();
	//	//y = getY();

	//	// check for legality
	//	// play move, reveal space, apply hp (if hit)
	//	doMove(x, y, b1);      // *************************** returns true if move was valid.

	//						   // check for endgame condition
	//	if (isGameOver(player1Ships)) {
	//		endGame();
	//	}


	//	// call player2 exe

	//	// get player2 move
	//	//x = getX();
	//	//y = getY();

	//	// check for legality
	//	// play move, reveal space, apply hp (if hit)
	//	doMove(x, y, b2);

	//	// check for endgame condition
	//	if (isGameOver(player2Ships)) {
	//		endGame();
	//	}
	//} while (true);
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
array<int^,1>^ readMove() {
	// read move.txt
	array<int^, 1>^ move;
	return move;
}

bool checkMoveLegality(int x, int y, Board* b) {
	if (b->getSpace(x, y)->revealed == true) return false; // move has already been made, illegal
	//MessageBox::Show("legal move");
	return true;
}

// player made illegal move
void illegalMove(int player) {
	MessageBox::Show("Player " + player + " made a bad move" );
	if (player == 1) endGame(2);
	endGame(1);
}


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

//// simple game function to take care of a single move
//bool doMove(int x, int y, Board b) {
//	Space* sp = b.getSpace(x, y);
//	if (sp->revealed == false) {  // is it a valid move?
//		if (sp->shipPresent) {    // is there a ship there?
//			sp->ship->hp--;       // decrement hp
//		}
//		sp->revealed = true;      // to show it has been guessed already
//		return true;
//	}
//	else {
//		return false;
//	}
//	updateGUI();
//}

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

void endGame(int winner) {

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

		player1HPLabel->Text = "hi"; // works !!

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

System::Void CppWinForm1::MyForm::player1HumanButton_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	return System::Void();
}

System::Void CppWinForm1::MyForm::player1PCButton_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	return System::Void();
}

System::Void CppWinForm1::MyForm::player1ConsoleCheckbox_CheckedChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	return System::Void();
}

System::Void CppWinForm1::MyForm::player2HumanButton_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	return System::Void();
}

System::Void CppWinForm1::MyForm::player2PCButton_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	return System::Void();
}

System::Void CppWinForm1::MyForm::player2ConsoleCheckbox_CheckedChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	return System::Void();
}

System::Void CppWinForm1::MyForm::resetButton_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	return System::Void();
}

System::Void CppWinForm1::MyForm::placeButton_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	return System::Void();
}

System::Void CppWinForm1::MyForm::showShipsCheckbox_CheckedChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	return System::Void();
}

System::Void CppWinForm1::MyForm::playButton_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	return System::Void();
}

System::Void CppWinForm1::MyForm::timeLimitComboBox_SelectedIndexChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	return System::Void();
}

