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
#include <string>

#include <windows.system.threading.h>
#include <atomic>


using namespace System;
using namespace System::Windows::Forms;
//using namespace std; // don't uncomment, causes problems

// variable declarations
const static int MAX_SHIP_COUNT = 20;
int numberOfShips;

int player1HP = 0;
int player2HP = 0;
Board* player1Board;
Board* player2Board;
bool player1isHuman = true;
bool player2isHuman = true;
bool showPlayer1Console = false;
bool showPlayer2Console = false;
bool showShips = false;
bool endgame = false;
int timeLimit = 1000; // in seconds
bool human1MadeMove = false;
bool human2MadeMove = false;

std::string player1LastMove;
int player1MoveCode;
std::string player2LastMove;
int player2MoveCode;

std::string turnString;

std::string player1PCPath;
std::string player2PCPath;

std::atomic<bool> stopTiming = false;
std::atomic<bool> exeP2 = false;
std::atomic<bool> exeP1 = false;
std::atomic<bool> executing = false;


// function declarations
void update(Control^ control, int x, int y, int player); // does a move
void illegalMove(int player); // player made an illegal move
void endGame(int winner); // player winner wins game
bool checkMoveLegality(int x,int y, Board* player1Board); // checks legality of move, true if legal, false if illegal
void buttonClicked(Control^ control, int x, int y, int clickee); // does actions after a move is manually input
array<String^,1>^ getSettings(); // reads in settings from settings.txt
void shipsFromFile(int player, Ship* ships[], array<String^,1>^ settings); // reads ships in from playerXships.txt
int getLFromString(String^ s);
int getWFromString(String^ s);
void callEXE(int player, int mode); // calls the exe of the specified player, in the specified mode
void runExe(Object^ data);
void timeLimiter(Object^ data);
void threadedWait(int ms);
void waitms(Object^ data);





[STAThread]
void Main(array<String^, 1>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);


	CppWinForm1::MyForm form;
	Application::Run(%form);



}

void buttonClicked(Control^ control, int x, int y, int clickee) {
	String^ managedString = "Player " + clickee + " Button at " + x + ", " + y + " pressed";

	// convert managed string to std::string
	//msclr::interop::marshal_context context;
	//std::string standardString = context.marshal_as<std::string>(managedString);

	// write to file
	//std::ofstream log;
	//log.open("log.txt");
	//log << standardString;
	//log.close();
	int player;
	if (clickee == 1) {
		player = 2;
	}
	else {
		player = 1;
	}

	update(control, x, y, player);


	//MessageBox::Show(managedString); // also useful for debugging woo!

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
int getLFromString(String^ s) {
	int yIndex = s->IndexOf("w");
	String^ substr = s->Substring(1, yIndex - 1);
	int xCoord = Convert::ToInt32(substr);
	return xCoord;
}

int getWFromString(String^ s) {
	int yIndex = s->IndexOf("w");
	String^ substr = s->Substring(yIndex + 1, s->Length - yIndex - 1);
	int yCoord = Convert::ToInt32(substr);
	return yCoord;
}


// update button appearance, player== clicker
void update(Control^ control, int x, int y, int player) {
	if (x < player1Board->dimension && y < player1Board->dimension) {
		if (player == 1) {
			// check for legality
			if (checkMoveLegality(x,y, player2Board) == false) illegalMove(1);
			turnString = "Player 2's turn";
			player2Board->getSpace(x, y)->revealed = true;
			if (player2Board->getSpace(x, y)->shipPresent) {
				// hit
				
					// display hit // handled inside if(shipremainingHP)
				
				// handle hit
					// decrement ship hp
				int shipRemainingHP = player2Board->getSpace(x, y)->ship->hit(x, y); // returns remaining hp
					// decrement player hp
				player2HP = player2HP - 1;
				
				//array<Control ^, 1>^ player1HPLabelarr = control->Parent->Parent->player1HPLabel->Text = "Total Ship HP Remaining:  " + player1HP;
				//Label ^ player1HPLabel = dynamic_cast<Label^>(player1HPLabelarr[0]);
				//player1HPLabel->Text = 
					// check for sunk
				if (shipRemainingHP == 0) { // sunk
					control->BackColor = System::Drawing::Color::Black;
					// convert managed string to std::string
					msclr::interop::marshal_context context;
					std::string standardString = context.marshal_as<std::string>("Player 1's last move: " + x + "," + y + ". Hit and sunk!");
					player1LastMove = standardString;
					player1MoveCode = 3;
				}
				else {
					control->BackColor = System::Drawing::Color::Red;
					// convert managed string to std::string
					msclr::interop::marshal_context context;
					std::string standardString = context.marshal_as<std::string>("Player 1's last move: " + x + "," + y + ". Hit!");
					player1LastMove = standardString;
					player1MoveCode = 2;
				}
				if (player2HP == 0) {
					//MessageBox::Show("Player 2 wins!");
					endGame(1);
						}
			}
			else {
				// miss
				control->BackColor = System::Drawing::Color::White;
				// display miss
				// convert managed string to std::string
				msclr::interop::marshal_context context;
				std::string standardString = context.marshal_as<std::string>("Player 1's last move: " + x + "," + y + ". Miss!");
				player1LastMove = standardString;
				player1MoveCode = 1;
			}
		}
		else {
			// check for legality
			if (checkMoveLegality(x, y, player1Board) == false) illegalMove(2);
			turnString = "Player 1's turn";
			player1Board->getSpace(x, y)->revealed = true;
			if (player1Board->getSpace(x, y)->shipPresent) {
				// hit

				// display hit // handled inside if(shipremainingHP)

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
					control->BackColor = System::Drawing::Color::Black;
					// convert managed string to std::string
					msclr::interop::marshal_context context;
					std::string standardString = context.marshal_as<std::string>("Player 2's last move: " + x + "," + y + ". Hit and sunk!");
					player2LastMove = standardString;
					player2MoveCode = 3;
				}
				else {
					control->BackColor = System::Drawing::Color::Red;
					// convert managed string to std::string
					msclr::interop::marshal_context context;
					std::string standardString = context.marshal_as<std::string>("Player 2's last move: " + x + "," + y + ". Hit!");
					player2LastMove = standardString;
					player2MoveCode = 2;
				}
				if (player1HP == 0) {
					//MessageBox::Show("Player 1 wins!");
					endGame(2);
				}
			}
			else {
				// miss
				control->BackColor = System::Drawing::Color::White;
				// display miss
				// convert managed string to std::string
				msclr::interop::marshal_context context;
				std::string standardString = context.marshal_as<std::string>("Player 2's last move: " + x + "," + y + ". Miss!");
				player2LastMove = standardString;
				player2MoveCode = 1;
			}
		}
		
	}
	else {
		
		if (player == 1) {
			MessageBox::Show("Player 2 made an illegal move!");
			endGame(1);
		}
		else {
			MessageBox::Show("Player 1 made an illegal move!");
			endGame(2);
		}
		// endgame with other player winning****************
	}
}

void initialize() {
	
	
	array<String^, 1>^ settings = getSettings();
	numberOfShips = int::Parse(settings[1]);
	
	if (player1isHuman == false) {
		callEXE(1, 1); // run player 1 ship placement, if not a program ,.txt file should already be present
	}

	Ship* player1Ships[MAX_SHIP_COUNT];
	shipsFromFile(1, player1Ships, settings);

	if (player2isHuman == false) {
		callEXE(2, 1); // run player 2 ship placement, if not a program ,.txt file should already be present
	}

	Ship* player2Ships[MAX_SHIP_COUNT];
	shipsFromFile(2, player2Ships, settings);
	

	// create boards
	player1Board = new Board(int::Parse(settings[0]), player1Ships, 1, numberOfShips);
	player2Board = new Board(int::Parse(settings[0]), player2Ships, 2, numberOfShips);

	player1HP = player1Board->totalHP;
	player2HP = player2Board->totalHP;

	turnString = "Player 1's turn";

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

// player, mode (1 == place, 2 == play)
void callEXE(int player, int mode) {
	//MessageBox::Show("callEXE called, player: " + player + " mode: " + mode);
	if (player == 1) {
		// spawn thread
		

		if (mode == 2) {
			System::Threading::Thread^ exeThread = gcnew
				System::Threading::Thread(gcnew System::Threading::ParameterizedThreadStart(runExe));
			array<String^,1>^ data = gcnew array<String^,1>(3){gcnew String( player1PCPath.c_str()),player.ToString(), mode.ToString() };
			exeThread->Start(data);

			System::Threading::Thread^ timerThread = gcnew
				System::Threading::Thread(gcnew System::Threading::ParameterizedThreadStart(timeLimiter));
			array<int^, 1>^ data2 = gcnew array<int^, 1>(2) { timeLimit, player };
			timerThread->Start(data2);

			//std::thread exe(runExe, player1PCPath, player, mode);
			//std::thread timer(timeLimiter, timeLimit);
			//// if mode == 2, time limit applies
			exeThread->Join();
			stopTiming = true;
			timerThread->Join();
		}
		else {
			System::Threading::Thread^ exeThread = gcnew
				System::Threading::Thread(gcnew System::Threading::ParameterizedThreadStart(runExe));
			array<String^, 1>^ data3 = gcnew array<String^, 1>(3) { gcnew String(player1PCPath.c_str()), player.ToString(), mode.ToString()};
			exeThread->Start(data3);
			exeThread->Join();
		}

		
	}
	else {
		if (mode == 2) {
			System::Threading::Thread^ exeThread = gcnew
				System::Threading::Thread(gcnew System::Threading::ParameterizedThreadStart(runExe));
			array<String^, 1>^ data = gcnew array<String^, 1>(3) { gcnew String(player2PCPath.c_str()), player.ToString(), mode.ToString() };
			exeThread->Start(data);

			System::Threading::Thread^ timerThread = gcnew
				System::Threading::Thread(gcnew System::Threading::ParameterizedThreadStart(timeLimiter));
			array<int^, 1>^ data2 = gcnew array<int^, 1>(2) { timeLimit, player };
			timerThread->Start(data2);

			//std::thread exe(runExe, player1PCPath, player, mode);
			//std::thread timer(timeLimiter, timeLimit);
			//// if mode == 2, time limit applies
			exeThread->Join();
			stopTiming = true;
			timerThread->Join();
		}
		else {
			System::Threading::Thread^ exeThread = gcnew
				System::Threading::Thread(gcnew System::Threading::ParameterizedThreadStart(runExe));
			array<String^, 1>^ data3 = gcnew array<String^, 1>(3) { gcnew String(player2PCPath.c_str()), player.ToString(), mode.ToString() };
			exeThread->Start(data3);
			exeThread->Join();
		}
	}
}

//void runExe(std::string path, int player, int mode) {
void runExe(Object^ data) {
	array<String^,1>^ strArr = dynamic_cast<array<String^,1>^>(data);
	msclr::interop::marshal_context context;
	std::string standardString = context.marshal_as<std::string>(" " + strArr[1]);
	std::string arg1 = standardString;

	standardString = context.marshal_as<std::string>(" " + strArr[2]);
	std::string arg2 = standardString;

	std::string fullcmd = context.marshal_as<std::string>(strArr[0]) + arg1 + arg2;
	const char * chars = fullcmd.c_str();
	system(chars);
}

// limit in secs
void timeLimiter(Object^ data) {
	array<int^, 1>^ intArr = dynamic_cast<array<int^, 1>^>(data);
	int msLimit = (int)intArr[0] * 1000;
	int waitInterval = 100; // ms to wait between checks
	while (stopTiming == false) {
		System::Threading::Thread::Sleep(waitInterval);
		msLimit = msLimit - waitInterval;
		if (msLimit <= 0) {
			// show grace dialog
			if (MessageBox::Show("Time limit reached, terminate?",
				"Disqualification", MessageBoxButtons::YesNo,
				MessageBoxIcon::Question) == DialogResult::Yes) {
			

			if (intArr[0] == 1) endGame(2);
			else endGame(1);
		}
		}
	}
	
}

void threadedWait(int ms) {
	System::Threading::Thread^ sleepThread = gcnew
		System::Threading::Thread(gcnew System::Threading::ParameterizedThreadStart(waitms));
	array<int^, 1>^ data = gcnew array<int^, 1>(1) { ms };
	sleepThread->Start(data);
	sleepThread->Join();
}

void waitms(Object^ data) {
	array<int^, 1>^ intArr = dynamic_cast<array<int^, 1>^>(data);
	System::Threading::Thread::Sleep((int)intArr[0]);
}

array<String^,1>^ getSettings() {
	std::string line;
	array<String^, 1>^ settings = gcnew array<String^,1>(MAX_SHIP_COUNT + 1); // ships + numberOfShips
	std::ifstream myfile("settings.txt");
	if (myfile.is_open())
	{
		int i = 0;
		while (getline(myfile , line ))
		{
			settings[i++] = gcnew String(line.c_str());
		}
		myfile.close();
	}

	else std::cout << "Unable to open file";
	return settings;
}
void shipsFromFile(int player, Ship* ships[], array<String^,1>^ settings) {

	

	std::string line;
	std::string temp;
	int tempX;
	int tempY;
	int tempL;
	int tempW;
	int orient;
	int dim;

					msclr::interop::marshal_context context;
				std::string standardString = context.marshal_as<std::string>("player" + player + "ships.txt");
				

	std::ifstream myfile(standardString);
	if (myfile.is_open())
	{

		dim = int::Parse(settings[0]); // maybe not needed
		
		numberOfShips = int::Parse(settings[1]);

		

		int i = 0;
		while (getline(myfile, line))
		{
			temp = line;
			tempX = getXFromCoordString(gcnew String(line.c_str()));
			tempY = getYFromCoordString(gcnew String(line.c_str()));
			getline(myfile, line);
			orient = int::Parse(gcnew String(line.c_str()));
			tempL = getLFromString(settings[i + 2]);
			tempW = getWFromString(settings[i + 2]);
			ships[i++] = new Ship(tempL, tempW, tempX, tempY, orient);
		}
		myfile.close();
	}

	else std::cout << "Unable to open file";

}

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
	else endGame(1);
}

void getMove(int* x, int* y, int player) {
	std::string line;
	
	msclr::interop::marshal_context context;
	std::string standardString = context.marshal_as<std::string>("player" + player + "move.txt");


	std::ifstream myfile(standardString);
	if (myfile.is_open())
	{
		
		while (getline(myfile, line))
		{
			*x = getXFromCoordString(gcnew String(line.c_str()));
			*y = getYFromCoordString(gcnew String(line.c_str()));
		}
		myfile.close();
	}
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
	MessageBox::Show("Player " + winner + " wins!");
	endgame = true;
}

System::Void CppWinForm1::MyForm::player1Button_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	
		//MessageBox::Show("You clicked on player 1's buttons!");
		Control^ senderControl = dynamic_cast<Control^>(sender);
		String^ coordString;
		if (senderControl != nullptr)
			coordString = dynamic_cast<String^>(senderControl->Tag);
		int x = getXFromCoordString(coordString);
		int y = getYFromCoordString(coordString);

		buttonClicked(senderControl, x, y, 1);

		player1HPLabel->Text = L"Total Ship HP Remaining:  " + player1HP;
		player2LastMoveLabel->Text = gcnew String(player2LastMove.c_str());
		whoseTurnLabel->Text = gcnew String(turnString.c_str());
		human2MadeMove = true;
		if (player1isHuman && player2isHuman) {
			for (int i = 0; i < player1Board->dimension; i++)
			{
				for (int j = 0; j < player1Board->dimension; j++)
				{
					player1Buttons[i, j]->Enabled = false;
					player2Buttons[i, j]->Enabled = true;
				}
			}
		}

		this->Update();

		// execute 'play' button code

		System::Threading::Thread^ playThread1 = gcnew
			System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &CppWinForm1::MyForm::loopThroughTurns));

		playThread1->Start();

		player2HPLabel->Text = L"Total Ship HP Remaining:  " + player2HP;
		player1LastMoveLabel->Text = gcnew String(player1LastMove.c_str());
		whoseTurnLabel->Text = gcnew String(turnString.c_str());
		player1HPLabel->Text = L"Total Ship HP Remaining:  " + player1HP;
		player2LastMoveLabel->Text = gcnew String(player2LastMove.c_str());
		whoseTurnLabel->Text = gcnew String(turnString.c_str());


		this->Update();
	
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

	player2HPLabel->Text = L"Total Ship HP Remaining:  " + player2HP;
	player1LastMoveLabel->Text = gcnew String(player1LastMove.c_str());
	whoseTurnLabel ->Text = gcnew String(turnString.c_str());
	human1MadeMove = true;

	if (player1isHuman && player2isHuman) {
		for (int i = 0; i < player1Board->dimension; i++)
		{
			for (int j = 0; j < player1Board->dimension; j++)
			{
				player2Buttons[i, j]->Enabled = false;
				player1Buttons[i, j]->Enabled = true;
			}
		}
	}

	this->Update();

	// execute 'play' button code

	System::Threading::Thread^ playThread1 = gcnew
		System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &CppWinForm1::MyForm::loopThroughTurns));

	playThread1->Start();

	player2HPLabel->Text = L"Total Ship HP Remaining:  " + player2HP;
	player1LastMoveLabel->Text = gcnew String(player1LastMove.c_str());
	whoseTurnLabel->Text = gcnew String(turnString.c_str());
	player1HPLabel->Text = L"Total Ship HP Remaining:  " + player1HP;
	player2LastMoveLabel->Text = gcnew String(player2LastMove.c_str());
	whoseTurnLabel->Text = gcnew String(turnString.c_str());


	this->Update();
}

System::Void CppWinForm1::MyForm::player1HumanButton_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	player1isHuman = true;
	std::string s = "Human";
	player1Label->Text = gcnew String(s.c_str());
}

System::Void CppWinForm1::MyForm::player1PCButton_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	// Displays an OpenFileDialog so the user can select a file.
	OpenFileDialog ^ openFileDialog1 = gcnew OpenFileDialog();
	openFileDialog1->Filter = "Executable File|*.exe";
	openFileDialog1->Title = "Select an executable File";

	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{

		String^ managedString = openFileDialog1->FileName;
		msclr::interop::marshal_context context;
		std::string standardString = context.marshal_as<std::string>(managedString);
		player1PCPath = standardString;
		//const char * chars = standardString.c_str();
		player1isHuman = false;
		player1Label->Text = gcnew String(player1PCPath.c_str());
		this->Update();
	}
}

System::Void CppWinForm1::MyForm::player1ConsoleCheckbox_CheckedChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	CheckBox^ senderControl = dynamic_cast<CheckBox^>(sender);
	if (senderControl->Checked == true) showPlayer1Console = true;
	else showPlayer1Console = false;
}

System::Void CppWinForm1::MyForm::player2HumanButton_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	player2isHuman = true;
	std::string s = "Human";
	player2Label->Text = gcnew String(s.c_str());
}

System::Void CppWinForm1::MyForm::player2PCButton_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	// Displays an OpenFileDialog so the user can select a file.
	OpenFileDialog ^ openFileDialog1 = gcnew OpenFileDialog();
	openFileDialog1->Filter = "Executable File|*.exe";
	openFileDialog1->Title = "Select an executable File";

	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{

		String^ managedString = openFileDialog1->FileName;
		msclr::interop::marshal_context context;
		std::string standardString = context.marshal_as<std::string>(managedString);
		player2PCPath = standardString;
		//const char * chars = standardString.c_str();
		player2isHuman = false;
		player2Label->Text = gcnew String(player2PCPath.c_str());
		this->Update();

	}
}

System::Void CppWinForm1::MyForm::player2ConsoleCheckbox_CheckedChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	CheckBox^ senderControl = dynamic_cast<CheckBox^>(sender);
	if (senderControl->Checked == true) showPlayer2Console = true;
	else showPlayer2Console = false;
}

System::Void CppWinForm1::MyForm::resetButton_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	int boardSize;
	int numShips;
	int length;
	int x, y, o;
	std::vector<int> lengths;
	bool v = true;
	std::ofstream out;
	
	out.open("settings.txt");

	std::cout << "Enter a board size: " << std::endl;
	std::cin >> boardSize;
	std::cout << "How many ships would you like?" << std::endl;
	std::cin >> numShips;
	out << boardSize << std::endl;
	out << numShips << std::endl;

	for (int a = 0; a < numShips; a++) {
		std::cout << "What length would you like this ship to be?" << std::endl;
		std::cin >> length;
		lengths.push_back(length);
	}

	bool p1 = false;
	if (player1isHuman) {
		std::ofstream placement;
		placement.open("player1ships.txt");
		std::cout << "Player1:" << std::endl;
		for (int i = 0; i < numShips; i++) {

			v = true;
			length = lengths[i];
			out << "l" << length << "w1" << std::endl;
			std::cout << "Enter the x coordinate for the ship: " << std::endl;
			std::cin >> x;
			while (x >= boardSize || x < 0) {
				std::cout << "invalid x.  Please enter a new x: " << std::endl;
				std::cin >> x;
			}
			std::cout << "Enter the y coordinate for the ship: " << std::endl;
			std::cin >> y;
			while (y >= boardSize || y < 0) {
				std::cout << "invalid y.  Please enter a new y: " << std::endl;
				std::cin >> y;
			}
			while (v) {
				std::cout << "Enter the orientation for the ship (1 = west, 2 = north, 3 = east, 4 = south)" << std::endl;
				std::cin >> o;
				if (o == 1) {
					if (x - length >= 0) {
						v = false;
					}
					else {
						std::cout << "invalid orientation.  Please enter a new orientation: " << std::endl;
					}
				}
				else if (o == 2) {
					if (y - length >= 0) {
						v = false;
					}
					else {
						std::cout << "invalid orientation.  Please enter a new orientation: " << std::endl;
					}
				}
				else if (o == 3) {
					if (x + length < boardSize) {
						v = false;
					}
					else {
						std::cout << "invalid orientation.  Please enter a new orientation: " << std::endl;
					}
				}
				else if (o == 4) {
					if (y + length < boardSize) {
						v = false;
					}
					else {
						std::cout << "invalid orientation.  Please enter a new orientation: " << std::endl;
					}
				}
				else {
					std::cout << "Invalid orientation.  Please enter a new orientation." << std::endl;
				}
			}
			placement << "x" << x << "y" << y << std::endl << o << std::endl;
		}
		placement.close();
		system("cls");
	}

	if (player2isHuman) {
		std::ofstream placement;
		placement.open("player2ships.txt");
		std::cout << "board size is " << boardSize << std::endl;
		std::cout << "Player 2:" << std::endl;
		for (int i = 0; i < numShips; i++) {

			v = true;
			//std::cout << "What length would you like this ship to be?" << std::endl;
			//std::cin >> length;
			length = lengths[i];
			
			std::cout << "length of ship: " << length << std::endl;
			//out << "l" << length << "w1" << std::endl;
			std::cout << "Enter the x coordinate for the ship: " << std::endl;
			std::cin >> x;
			while (x >= boardSize || x < 0) {
				std::cout << "invalid x.  Please enter a new x: " << std::endl;
				std::cin >> x;
			}
			std::cout << "Enter the y coordinate for the ship: " << std::endl;
			std::cin >> y;
			while (y >= boardSize || y < 0) {
				std::cout << "invalid y.  Please enter a new y: " << std::endl;
				std::cin >> y;
			}
			while (v) {
				std::cout << "Enter the orientation for the ship (1 = west, 2 = north, 3 = east, 4 = south)" << std::endl;
				std::cin >> o;
				if (o == 1) {
					if (x - length >= 0) {
						v = false;
					}
					else {
						std::cout << "invalid orientation.  Please enter a new orientation: " << std::endl;
					}
				}
				else if (o == 2) {
					if (y - length >= 0) {
						v = false;
					}
					else {
						std::cout << "invalid orientation.  Please enter a new orientation: " << std::endl;
					}
				}
				else if (o == 3) {
					if (x + length < boardSize) {
						v = false;
					}
					else {
						std::cout << "invalid orientation.  Please enter a new orientation: " << std::endl;
					}
				}
				else if (o == 4) {
					if (y + length < boardSize) {
						v = false;
					}
					else {
						std::cout << "invalid orientation.  Please enter a new orientation: " << std::endl;
					}
				}
				else {
					std::cout << "Invalid orientation.  Please enter a new orientation." << std::endl;
				}
			}
			placement << "x" << x << "y" << y << std::endl << o << std::endl;
		}
		placement.close();
		system("cls");
	}
	out.close();
	return System::Void();
}

System::Void CppWinForm1::MyForm::placeButton_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	initialize();

	int maxDim = player1Board->MAX_BOARD_SIZE;
	int gameDim = player1Board->dimension;
	for (int i = 0; i < maxDim; i++)
	{
		for (int j = 0; j < maxDim; j++)
		{
			if (i >= gameDim || j >= gameDim) {// disable out of bounds buttons
				player1Buttons[i, j]->Enabled = false;
				player2Buttons[i, j]->Enabled = false;

				player1Buttons[i, j]->Visible = false;
				player2Buttons[i, j]->Visible = false;
			}
			else { // enable in bounds buttons
				player1Buttons[i, j]->Enabled = true;
				player2Buttons[i, j]->Enabled = true;
				player1Buttons[i, j]->Visible = true;
				player2Buttons[i, j]->Visible = true;
				player1Buttons[i, j]->BackColor = System::Drawing::Color::SkyBlue;
				player2Buttons[i, j]->BackColor = System::Drawing::Color::SkyBlue;
			}

		}
	}

	
		for (int i = 0; i < player1Board->dimension; i++)
		{
			for (int j = 0; j < player1Board->dimension; j++)
			{
				if (player1isHuman == false) {
					player2Buttons[i, j]->Enabled = false;
				}
				if (player2isHuman == false) {
					player1Buttons[i, j]->Enabled = false;
				}
			}
		}
	


	player1HPLabel->Text = L"Total Ship HP Remaining:  " + player1HP;
	player2HPLabel->Text = L"Total Ship HP Remaining:  " + player2HP;
	whoseTurnLabel->Text = L"Player 1's Turn";
}

System::Void CppWinForm1::MyForm::showShipsCheckbox_CheckedChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	CheckBox^ senderControl = dynamic_cast<CheckBox^>(sender);
	if (senderControl->Checked == true) showShips = true;
	else showShips = false;
}
//void CppWinForm1::MyForm::player1Turn() {
//	int* x = new int();
//	int* y = new int();
//	std::string boardString;
//
//	// player1 turn
//	if (player1isHuman == false) {
//		msclr::interop::marshal_context context;
//		std::string standardString = context.marshal_as<std::string>(player2Board->dimension + "\n");
//		boardString = standardString;
//		for (int i = 0; i < player2Board->dimension; i++)
//		{
//			for (int j = 0; j < player2Board->dimension; j++)
//			{
//				if (player2Buttons[i, j]->BackColor == System::Drawing::Color::SkyBlue) {
//					boardString = boardString + "0";
//				}
//				else if (player2Buttons[i, j]->BackColor == System::Drawing::Color::White) {
//					boardString = boardString + "1";
//				}
//				else if (player2Buttons[i, j]->BackColor == System::Drawing::Color::Red) {
//					boardString = boardString + "2";
//				}
//				if (player2Buttons[i, j]->BackColor == System::Drawing::Color::Black) {
//					boardString = boardString + "3";
//				}
//				if (j == player2Board->dimension - 1) {
//					boardString = boardString + " ";
//				}
//
//			}
//			boardString = boardString + "\n";
//		}
//
//		// write to file
//		std::ofstream board;
//		board.open("board.txt");
//		board << boardString;
//		board.close();
//
//		callEXE(1, 2);
//
//		getMove(x, y, 1);
//		buttonClicked(player2Buttons[*x, *y], *x, *y, 1);
//	}
//	else {
//		while (human1MadeMove == false) {
//			Sleep(100);
//		}
//		human1MadeMove = false;
//	}
//	executing = false;
//	exeP2 = true;
//}
//
//	void CppWinForm1::MyForm::player2Turn() {
//		int* x = new int();
//		int* y = new int();
//		std::string boardString;
//
//
//		if (player2isHuman == false) {
//			msclr::interop::marshal_context context;
//			std::string standardString = context.marshal_as<std::string>(player2Board->dimension + "\n");
//			boardString = standardString;
//			for (int i = 0; i < player2Board->dimension; i++)
//			{
//				for (int j = 0; j < player2Board->dimension; j++)
//				{
//					if (player1Buttons[i, j]->BackColor == System::Drawing::Color::SkyBlue) {
//						boardString = boardString + "0";
//					}
//					else if (player1Buttons[i, j]->BackColor == System::Drawing::Color::White) {
//						boardString = boardString + "1";
//					}
//					else if (player1Buttons[i, j]->BackColor == System::Drawing::Color::Red) {
//						boardString = boardString + "2";
//					}
//					if (player1Buttons[i, j]->BackColor == System::Drawing::Color::Black) {
//						boardString = boardString + "3";
//					}
//					if (j == player1Board->dimension - 1) {
//						boardString = boardString + " ";
//					}
//
//				}
//				boardString = boardString + "\n";
//			}
//
//			// write to file
//			std::ofstream board;
//			board.open("board.txt");
//			board << boardString;
//			board.close();
//
//			callEXE(2, 2);
//
//			getMove(x, y, 2);
//			buttonClicked(player1Buttons[*x, *y], *x, *y, 2);
//
//			player1HPLabel->Text = L"Total Ship HP Remaining:  " + player1HP;
//			player2LastMoveLabel->Text = gcnew String(player2LastMove.c_str());
//			whoseTurnLabel->Text = gcnew String(turnString.c_str());
//			this->Update();
//		}
//		else {
//			while (human2MadeMove == false) {
//				Sleep(100);
//			}
//			human1MadeMove = false;
//		}
//		executing = false;
//		exeP1 = true;
//	}
void CppWinForm1::MyForm::loopThroughTurns() {
	int* x = new int();
	int* y = new int();
	std::string boardString;
	//while (endgame == false) {
		// write board





		// player1 turn
		if (player1isHuman == false) {
			msclr::interop::marshal_context context;
			std::string standardString = context.marshal_as<std::string>(player2Board->dimension + "\n");
			boardString = standardString;
			for (int i = 0; i < player2Board->dimension; i++)
			{
				for (int j = 0; j < player2Board->dimension; j++)
				{
					if (player2Buttons[i, j]->BackColor == System::Drawing::Color::SkyBlue) {
						boardString = boardString + "0";
					}
					else if (player2Buttons[i, j]->BackColor == System::Drawing::Color::White) {
						boardString = boardString + "1";
					}
					else if (player2Buttons[i, j]->BackColor == System::Drawing::Color::Red) {
						boardString = boardString + "2";
					}
					if (player2Buttons[i, j]->BackColor == System::Drawing::Color::Black) {
						boardString = boardString + "3";
					}
					if (j == player2Board->dimension - 1) {
						boardString = boardString + " ";
					}

				}
				boardString = boardString + "\n";
			}

			// write to file
			std::ofstream board;
			board.open("board.txt");
			board << boardString;
			board.close();

			callEXE(1, 2);

			getMove(x, y, 1);
			buttonClicked(player2Buttons[*x, *y], *x, *y, 2);

			//player2HPLabel->Text = L"Total Ship HP Remaining:  " + player2HP;
			//player1LastMoveLabel->Text = gcnew String(player1LastMove.c_str());
			//whoseTurnLabel->Text = gcnew String(turnString.c_str());
			//this->Update();
		}
		else {
			while (human1MadeMove == false) {
				Sleep(100);
			}
			human1MadeMove = false;
		}


		if (endgame == false) {
			// player2 turn



			if (player2isHuman == false) {
				msclr::interop::marshal_context context;
				std::string standardString = context.marshal_as<std::string>(player2Board->dimension + "\n");
				boardString = standardString;
				for (int i = 0; i < player2Board->dimension; i++)
				{
					for (int j = 0; j < player2Board->dimension; j++)
					{
						if (player1Buttons[i, j]->BackColor == System::Drawing::Color::SkyBlue) {
							boardString = boardString + "0";
						}
						else if (player1Buttons[i, j]->BackColor == System::Drawing::Color::White) {
							boardString = boardString + "1";
						}
						else if (player1Buttons[i, j]->BackColor == System::Drawing::Color::Red) {
							boardString = boardString + "2";
						}
						if (player1Buttons[i, j]->BackColor == System::Drawing::Color::Black) {
							boardString = boardString + "3";
						}
						if (j == player1Board->dimension - 1) {
							boardString = boardString + " ";
						}

					}
					boardString = boardString + "\n";
				}

				// write to file
				std::ofstream board;
				board.open("board.txt");
				board << boardString;
				board.close();

				callEXE(2, 2);

				getMove(x, y, 2);
				buttonClicked(player1Buttons[*x, *y], *x, *y, 1);

				//player1HPLabel->Text = L"Total Ship HP Remaining:  " + player1HP;
				//player2LastMoveLabel->Text = gcnew String(player2LastMove.c_str());
				//whoseTurnLabel->Text = gcnew String(turnString.c_str());
				//this->Update();
			}
			else {
				while (human2MadeMove == false) {
					Sleep(100);
				}
				human1MadeMove = false;
			}
		}
	//}
}

// play button clicked when both players are non-human
System::Void CppWinForm1::MyForm::playButton_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	System::Threading::Thread^ playThread1 = gcnew
					System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &CppWinForm1::MyForm::loopThroughTurns));

				playThread1->Start();
				playThread1->Join();

				player2HPLabel->Text = L"Total Ship HP Remaining:  " + player2HP;
				player1LastMoveLabel->Text = gcnew String(player1LastMove.c_str());
				whoseTurnLabel->Text = gcnew String(turnString.c_str());
				player1HPLabel->Text = L"Total Ship HP Remaining:  " + player1HP;
				player2LastMoveLabel->Text = gcnew String(player2LastMove.c_str());
				whoseTurnLabel->Text = gcnew String(turnString.c_str());


				this->Update();
				// workaround: only plays one turn;



	//// spin off thread to loop
	//exeP1 = true;
	//exeP2 = false;
	//executing = false;
	//while (endgame == false) {
	//	if (executing == false) {
	//		if (exeP1) {
	//			executing = true;
	//			exeP1 = false;

	//		System::Threading::Thread^ playThread1 = gcnew
	//			System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &CppWinForm1::MyForm::player1Turn));

	//		player2HPLabel->Text = L"Total Ship HP Remaining:  " + player2HP;
	//		player1LastMoveLabel->Text = gcnew String(player1LastMove.c_str());
	//		whoseTurnLabel->Text = gcnew String(turnString.c_str());
	//		this->Update();

	//		playThread1->Start();
	//	}
	//		if(exeP2){
	//			if (endgame == false) {
	//				executing = true;
	//				exeP2 = false;
	//				System::Threading::Thread^ playThread2 = gcnew
	//					System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &CppWinForm1::MyForm::player2Turn));

	//				player1HPLabel->Text = L"Total Ship HP Remaining:  " + player1HP;
	//				player2LastMoveLabel->Text = gcnew String(player2LastMove.c_str());
	//				whoseTurnLabel->Text = gcnew String(turnString.c_str());
	//				this->Update();

	//				playThread2->Start();
	//			}
	//	}
	//}
	//}
}

System::Void CppWinForm1::MyForm::timeLimitComboBox_SelectedIndexChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	ComboBox^ senderControl = dynamic_cast<ComboBox^>(sender);
	int temp = senderControl->SelectedIndex;
	switch (temp) {
	case 0:
		timeLimit = 1000;
		break;
	case 1:
		timeLimit = 1;
		break;
	case 2:
		timeLimit = 2;
		break;
	case 3:
		timeLimit = 3;
		break;
	case 4:
		timeLimit = 4;
		break;
	case 5:
		timeLimit = 5;
		break;
	}
}

