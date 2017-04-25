#pragma once

namespace CppWinForm1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:
	public: System::Windows::Forms::Panel^  player2Panel;
	public: System::Windows::Forms::Panel^  player1Panel;
	public: System::Windows::Forms::Label^  verticalLabel;
	public: System::Windows::Forms::Label^  horizontalLabel;
	public: System::Windows::Forms::Label^  horizontalLabel2;
			const int BOARD_SIZE = 20;
	public: array<System::Windows::Forms::Button^, 2>^ player1Buttons = gcnew array<System::Windows::Forms::Button^, 2>(BOARD_SIZE, BOARD_SIZE);
	public: array<System::Windows::Forms::Button^, 2>^ player2Buttons = gcnew array<System::Windows::Forms::Button^, 2>(BOARD_SIZE, BOARD_SIZE);
	public: System::Windows::Forms::Panel^  controlPanel;
	protected:

	protected:
	public: System::Windows::Forms::GroupBox^  player2Box;
	public: System::Windows::Forms::Label^  player2HPLabel;

	public: System::Windows::Forms::CheckBox^  player2ConsoleCheckbox;
	public: System::Windows::Forms::Label^  player2Label;
	public: System::Windows::Forms::Button^  player2PCButton;
	public: System::Windows::Forms::Button^  player2HumanButton;
	public: System::Windows::Forms::GroupBox^  controlBox;
	public: System::Windows::Forms::Label^  player2LastMoveLabel;
	public: System::Windows::Forms::Label^  player1LastMoveLabel;
	public: System::Windows::Forms::Label^  whoseTurnLabel;
	public: System::Windows::Forms::Button^  playButton;
	public: System::Windows::Forms::CheckBox^  showShipsCheckbox;
	public: System::Windows::Forms::Button^  placeButton;
	public: System::Windows::Forms::Button^  resetButton;
	public: System::Windows::Forms::GroupBox^  player1Box;
	public: System::Windows::Forms::Label^  player1HPLabel;

	public: System::Windows::Forms::CheckBox^  player1ConsoleCheckbox;
	public: System::Windows::Forms::Label^  player1Label;
	public: System::Windows::Forms::Button^  player1PCButton;
	public: System::Windows::Forms::Button^  player1HumanButton;
	public: System::Windows::Forms::Label^  timeLimitLabel;
	public: System::Windows::Forms::ComboBox^  timeLimitComboBox;

	public:

	private:


	public:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{

			this->player2Panel = (gcnew System::Windows::Forms::Panel());

			this->verticalLabel = (gcnew System::Windows::Forms::Label());
			this->horizontalLabel = (gcnew System::Windows::Forms::Label());
			this->horizontalLabel2 = (gcnew System::Windows::Forms::Label());
			this->player1Panel = (gcnew System::Windows::Forms::Panel());

			// instantiate buttons
			for (int i = 0; i < BOARD_SIZE; i++)
			{
				for (int j = 0; j < BOARD_SIZE; j++)
				{
					this->player1Buttons[i, j] = (gcnew System::Windows::Forms::Button());
					this->player2Buttons[i, j] = (gcnew System::Windows::Forms::Button());
				}
			}

			this->controlPanel = (gcnew System::Windows::Forms::Panel());
			this->player1Box = (gcnew System::Windows::Forms::GroupBox());
			this->controlBox = (gcnew System::Windows::Forms::GroupBox());
			this->player1HumanButton = (gcnew System::Windows::Forms::Button());
			this->player1PCButton = (gcnew System::Windows::Forms::Button());
			this->player1Label = (gcnew System::Windows::Forms::Label());
			this->player1ConsoleCheckbox = (gcnew System::Windows::Forms::CheckBox());
			this->player1HPLabel = (gcnew System::Windows::Forms::Label());
			this->player2Box = (gcnew System::Windows::Forms::GroupBox());
			this->player2HPLabel = (gcnew System::Windows::Forms::Label());
			this->player2ConsoleCheckbox = (gcnew System::Windows::Forms::CheckBox());
			this->player2Label = (gcnew System::Windows::Forms::Label());
			this->player2PCButton = (gcnew System::Windows::Forms::Button());
			this->player2HumanButton = (gcnew System::Windows::Forms::Button());
			this->resetButton = (gcnew System::Windows::Forms::Button());
			this->placeButton = (gcnew System::Windows::Forms::Button());
			this->showShipsCheckbox = (gcnew System::Windows::Forms::CheckBox());
			this->playButton = (gcnew System::Windows::Forms::Button());
			this->whoseTurnLabel = (gcnew System::Windows::Forms::Label());
			this->player1LastMoveLabel = (gcnew System::Windows::Forms::Label());
			this->player2LastMoveLabel = (gcnew System::Windows::Forms::Label());
			this->timeLimitLabel = (gcnew System::Windows::Forms::Label());
			this->timeLimitComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->controlPanel->SuspendLayout();
			this->player1Box->SuspendLayout();
			this->controlBox->SuspendLayout();
			this->player2Box->SuspendLayout();

			this->player2Panel->SuspendLayout();
			this->SuspendLayout();



			for (int i = 0; i < BOARD_SIZE; i++)
			{
				for (int j = 0; j < BOARD_SIZE; j++)
				{
					this->player2Panel->Controls->Add(this->player2Buttons[i, j]);
					this->player1Panel->Controls->Add(this->player1Buttons[i, j]);
				}
			}

			// 
			// player2Panel
			// 
			/////////this->player2Panel->Controls->Add(this->button301);
			this->player2Panel->Location = System::Drawing::Point(800, 50);
			this->player2Panel->Name = L"player2Panel";
			this->player2Panel->Size = System::Drawing::Size(502, 500);
			this->player2Panel->TabIndex = 1;
			this->player2Panel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			// 
			// player1Panel
			// 
			this->player1Panel->Location = System::Drawing::Point(270, 50);
			this->player1Panel->Name = L"player1Panel";
			this->player1Panel->Size = System::Drawing::Size(502, 500);
			this->player1Panel->TabIndex = 2;
			this->player1Panel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;

			// 
			// verticalLabel
			// 
			this->verticalLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.4F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->verticalLabel->Location = System::Drawing::Point(770, 50);
			this->verticalLabel->Name = L"verticalLabel";
			this->verticalLabel->Size = System::Drawing::Size(34, 500);
			this->verticalLabel->TabIndex = 2;
			this->verticalLabel->Text = L"0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19";

			// 
			// horizontalLabel
			// 
			this->horizontalLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->horizontalLabel->Location = System::Drawing::Point(273, 30);
			this->horizontalLabel->Name = L"horizontalLabel";
			this->horizontalLabel->Size = System::Drawing::Size(511, 29);
			this->horizontalLabel->TabIndex = 2;
			this->horizontalLabel->Text = L"0   1   2   3   4   5   6   7   8   9  10 11 12 13 14 15 16 17 18 19";

			// 
			// horizontalLabel2
			// 
			this->horizontalLabel2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->horizontalLabel2->Location = System::Drawing::Point(803, 30);
			this->horizontalLabel2->Name = L"horizontalLabel";
			this->horizontalLabel2->Size = System::Drawing::Size(511, 29);
			this->horizontalLabel2->TabIndex = 2;
			this->horizontalLabel2->Text = L"0   1   2   3   4   5   6   7   8   9  10 11 12 13 14 15 16 17 18 19";

			// set button properties
			for (int i = 0; i < BOARD_SIZE; i++)
			{
				for (int j = 0; j < BOARD_SIZE; j++)
				{
					this->player1Buttons[i, j]->Location = System::Drawing::Point(i * 25, j * 25);
					this->player1Buttons[i, j]->Margin = System::Windows::Forms::Padding(0);
					this->player1Buttons[i, j]->Name = L"player1Buttonx" + i + "y" + j;
					this->player1Buttons[i, j]->Size = System::Drawing::Size(25, 25);
					this->player1Buttons[i, j]->TabStop = false;
					this->player1Buttons[i, j]->Tag = L"x" + i + "y" + j;

					this->player2Buttons[i, j]->Location = System::Drawing::Point(i * 25, j * 25);
					this->player2Buttons[i, j]->Margin = System::Windows::Forms::Padding(0);
					this->player2Buttons[i, j]->Name = L"player1Buttonx" + i + "y" + j;
					this->player2Buttons[i, j]->Size = System::Drawing::Size(25, 25);
					this->player2Buttons[i, j]->TabStop = false;
					this->player2Buttons[i, j]->Tag = L"x" + i + "y" + j;

					this->player1Buttons[i, j]->Click += gcnew System::EventHandler(this, &MyForm::player1Button_Click); // add event listeners
					this->player2Buttons[i, j]->Click += gcnew System::EventHandler(this, &MyForm::player2Button_Click);

				}
			}

			//// 
			//// button400
			//// 
			//this->button400->Location = System::Drawing::Point(27, 402);
			//this->button400->Margin = System::Windows::Forms::Padding(0);
			//this->button400->Name = L"button400";
			//this->button400->Size = System::Drawing::Size(25, 25);
			//this->button400->TabIndex = 307;
			//this->button400->Text = L"button400";
			//this->button400->UseVisualStyleBackColor = true;
			// 
			// controlPanel
			// 
			this->controlPanel->Controls->Add(this->player2Box);
			this->controlPanel->Controls->Add(this->controlBox);
			this->controlPanel->Controls->Add(this->player1Box);
			this->controlPanel->Location = System::Drawing::Point(10, 50);
			this->controlPanel->Name = L"controlPanel";
			this->controlPanel->Size = System::Drawing::Size(250, 500);
			this->controlPanel->TabIndex = 0;
			// 
			// player1Box
			// 
			this->player1Box->Controls->Add(this->player1HPLabel);
			this->player1Box->Controls->Add(this->player1ConsoleCheckbox);
			this->player1Box->Controls->Add(this->player1Label);
			this->player1Box->Controls->Add(this->player1PCButton);
			this->player1Box->Controls->Add(this->player1HumanButton);
			this->player1Box->Location = System::Drawing::Point(3, 3);
			this->player1Box->Name = L"player1Box";
			this->player1Box->Size = System::Drawing::Size(244, 139);
			this->player1Box->TabIndex = 0;
			this->player1Box->TabStop = false;
			this->player1Box->Text = L"Player 1";
			// 
			// controlBox
			// 
			this->controlBox->Controls->Add(this->player2LastMoveLabel);
			this->controlBox->Controls->Add(this->player1LastMoveLabel);
			this->controlBox->Controls->Add(this->whoseTurnLabel);
			this->controlBox->Controls->Add(this->playButton);
			this->controlBox->Controls->Add(this->showShipsCheckbox);
			this->controlBox->Controls->Add(this->placeButton);
			this->controlBox->Controls->Add(this->resetButton);
			this->controlBox->Controls->Add(this->timeLimitLabel);
			this->controlBox->Controls->Add(this->timeLimitComboBox);
			this->controlBox->Location = System::Drawing::Point(3, 293);
			this->controlBox->Name = L"controlBox";
			this->controlBox->Size = System::Drawing::Size(244, 204);
			this->controlBox->TabIndex = 2;
			this->controlBox->TabStop = false;
			this->controlBox->Text = L"Control";
			// 
			// player1HumanButton
			// 
			this->player1HumanButton->Location = System::Drawing::Point(6, 19);
			this->player1HumanButton->Name = L"player1HumanButton";
			this->player1HumanButton->Size = System::Drawing::Size(87, 25);
			this->player1HumanButton->TabIndex = 0;
			this->player1HumanButton->Text = L"Human";
			this->player1HumanButton->UseVisualStyleBackColor = true;
			this->player1HumanButton->Click += gcnew System::EventHandler(this, &MyForm::player1HumanButton_Click);
			// 
			// player1PCButton
			// 
			this->player1PCButton->Location = System::Drawing::Point(109, 19);
			this->player1PCButton->Name = L"player1PCButton";
			this->player1PCButton->Size = System::Drawing::Size(100, 25);
			this->player1PCButton->TabIndex = 1;
			this->player1PCButton->Text = L"Computer...";
			this->player1PCButton->UseVisualStyleBackColor = true;
			this->player1PCButton->Click += gcnew System::EventHandler(this, &MyForm::player1PCButton_Click);
			// 
			// player1Label
			// 
			this->player1Label->AutoSize = true;
			this->player1Label->Location = System::Drawing::Point(6, 47);
			this->player1Label->Name = L"player1Label";
			this->player1Label->Size = System::Drawing::Size(41, 13);
			this->player1Label->TabIndex = 2;
			this->player1Label->Text = L"Human";
			// 
			// player1ConsoleCheckbox
			// 
			this->player1ConsoleCheckbox->AutoSize = true;
			this->player1ConsoleCheckbox->Location = System::Drawing::Point(6, 63);
			this->player1ConsoleCheckbox->Name = L"player1ConsoleCheckbox";
			this->player1ConsoleCheckbox->Size = System::Drawing::Size(184, 17);
			this->player1ConsoleCheckbox->TabIndex = 3;
			this->player1ConsoleCheckbox->Text = L"Show Player 1\'s Console Window";
			this->player1ConsoleCheckbox->UseVisualStyleBackColor = true;
			this->player1ConsoleCheckbox->CheckedChanged += gcnew System::EventHandler(this, &MyForm::player1ConsoleCheckbox_CheckedChanged);
			// 
			// player1HPLabel
			// 
			this->player1HPLabel->AutoSize = true;
			this->player1HPLabel->Location = System::Drawing::Point(6, 83);
			this->player1HPLabel->Name = L"player1HPLabel";
			this->player1HPLabel->Size = System::Drawing::Size(120, 13);
			this->player1HPLabel->TabIndex = 4;
			this->player1HPLabel->Text = L"Total Ship HP Remaining:  __";
			// 
			// player2Box
			// 
			this->player2Box->Controls->Add(this->player2HPLabel);
			this->player2Box->Controls->Add(this->player2ConsoleCheckbox);
			this->player2Box->Controls->Add(this->player2Label);
			this->player2Box->Controls->Add(this->player2PCButton);
			this->player2Box->Controls->Add(this->player2HumanButton);
			this->player2Box->Location = System::Drawing::Point(3, 148);
			this->player2Box->Name = L"player2Box";
			this->player2Box->Size = System::Drawing::Size(244, 139);
			this->player2Box->TabIndex = 5;
			this->player2Box->TabStop = false;
			this->player2Box->Text = L"Player 2";
			// 
			// player2HPLabel
			// 
			this->player2HPLabel->AutoSize = true;
			this->player2HPLabel->Location = System::Drawing::Point(6, 83);
			this->player2HPLabel->Name = L"player2HPLabel";
			this->player2HPLabel->Size = System::Drawing::Size(120, 13);
			this->player2HPLabel->TabIndex = 4;
			this->player2HPLabel->Text = L"Total Ship HP Remaining:  __";
			// 
			// player2ConsoleCheckbox
			// 
			this->player2ConsoleCheckbox->AutoSize = true;
			this->player2ConsoleCheckbox->Location = System::Drawing::Point(6, 63);
			this->player2ConsoleCheckbox->Name = L"player2ConsoleCheckbox";
			this->player2ConsoleCheckbox->Size = System::Drawing::Size(184, 17);
			this->player2ConsoleCheckbox->TabIndex = 3;
			this->player2ConsoleCheckbox->Text = L"Show Player 2\'s Console Window";
			this->player2ConsoleCheckbox->UseVisualStyleBackColor = true;
			this->player2ConsoleCheckbox->CheckedChanged += gcnew System::EventHandler(this, &MyForm::player2ConsoleCheckbox_CheckedChanged);
			// 
			// player2Label
			// 
			this->player2Label->AutoSize = true;
			this->player2Label->Location = System::Drawing::Point(6, 47);
			this->player2Label->Name = L"player2Label";
			this->player2Label->Size = System::Drawing::Size(41, 13);
			this->player2Label->TabIndex = 2;
			this->player2Label->Text = L"Human";
			// 
			// player2PCButton
			// 
			this->player2PCButton->Location = System::Drawing::Point(109, 19);
			this->player2PCButton->Name = L"player2PCButton";
			this->player2PCButton->Size = System::Drawing::Size(100, 25);
			this->player2PCButton->TabIndex = 1;
			this->player2PCButton->Text = L"Computer...";
			this->player2PCButton->UseVisualStyleBackColor = true;
			this->player2PCButton->Click += gcnew System::EventHandler(this, &MyForm::player2PCButton_Click);
			// 
			// player2HumanButton
			// 
			this->player2HumanButton->Location = System::Drawing::Point(6, 19);
			this->player2HumanButton->Name = L"player2HumanButton";
			this->player2HumanButton->Size = System::Drawing::Size(87, 25);
			this->player2HumanButton->TabIndex = 0;
			this->player2HumanButton->Text = L"Human";
			this->player2HumanButton->UseVisualStyleBackColor = true;
			this->player2HumanButton->Click += gcnew System::EventHandler(this, &MyForm::player2HumanButton_Click);
			// 
			// resetButton
			// 
			this->resetButton->Location = System::Drawing::Point(6, 19);
			this->resetButton->Name = L"resetButton";
			this->resetButton->Size = System::Drawing::Size(87, 29);
			this->resetButton->TabIndex = 0;
			this->resetButton->Text = L"Reset";
			this->resetButton->UseVisualStyleBackColor = true;
			this->resetButton->Click += gcnew System::EventHandler(this, &MyForm::resetButton_Click);
			// 
			// placeButton
			// 
			this->placeButton->Location = System::Drawing::Point(6, 54);
			this->placeButton->Name = L"placeButton";
			this->placeButton->Size = System::Drawing::Size(87, 29);
			this->placeButton->TabIndex = 1;
			this->placeButton->Text = L"Place Ships";
			this->placeButton->UseVisualStyleBackColor = true;
			this->placeButton->Click += gcnew System::EventHandler(this, &MyForm::placeButton_Click);
			// 
			// showShipsCheckbox
			// 
			this->showShipsCheckbox->AutoSize = true;
			this->showShipsCheckbox->Location = System::Drawing::Point(93, 61);
			this->showShipsCheckbox->Name = L"showShipsCheckbox";
			this->showShipsCheckbox->Size = System::Drawing::Size(145, 17);
			this->showShipsCheckbox->TabIndex = 2;
			this->showShipsCheckbox->Text = L"Show initial ship positions";
			this->showShipsCheckbox->UseVisualStyleBackColor = true;
			this->showShipsCheckbox->CheckedChanged += gcnew System::EventHandler(this, &MyForm::showShipsCheckbox_CheckedChanged);
			// 
			// playButton
			// 
			this->playButton->Location = System::Drawing::Point(6, 89);
			this->playButton->Name = L"playButton";
			this->playButton->Size = System::Drawing::Size(87, 29);
			this->playButton->TabIndex = 3;
			this->playButton->Text = L"Play";
			this->playButton->UseVisualStyleBackColor = true;
			this->playButton->Click += gcnew System::EventHandler(this, &MyForm::playButton_Click);
			// 
			// whoseTurnLabel
			// 
			this->whoseTurnLabel->AutoSize = true;
			this->whoseTurnLabel->Location = System::Drawing::Point(6, 121);
			this->whoseTurnLabel->Name = L"whoseTurnLabel";
			this->whoseTurnLabel->Size = System::Drawing::Size(73, 13);
			this->whoseTurnLabel->TabIndex = 4;
			this->whoseTurnLabel->Text = L"Player _\'s turn";
			// 
			// player1LastMoveLabel
			// 
			this->player1LastMoveLabel->AutoSize = true;
			this->player1LastMoveLabel->Location = System::Drawing::Point(6, 153);
			this->player1LastMoveLabel->Name = L"player1LastMoveLabel";
			this->player1LastMoveLabel->Size = System::Drawing::Size(121, 13);
			this->player1LastMoveLabel->TabIndex = 5;
			this->player1LastMoveLabel->Text = L"Player 1\'s last move: _,_";
			// 
			// player2LastMoveLabel
			// 
			this->player2LastMoveLabel->AutoSize = true;
			this->player2LastMoveLabel->Location = System::Drawing::Point(6, 166);
			this->player2LastMoveLabel->Name = L"player2LastMoveLabel";
			this->player2LastMoveLabel->Size = System::Drawing::Size(121, 13);
			this->player2LastMoveLabel->TabIndex = 6;
			this->player2LastMoveLabel->Text = L"Player 2\'s last move: _,_";
			// 
			// timeLimitLabel
			// 
			this->timeLimitLabel->AutoSize = true;
			this->timeLimitLabel->Location = System::Drawing::Point(120, 102);
			this->timeLimitLabel->Name = L"timeLimitLabel";
			this->timeLimitLabel->Size = System::Drawing::Size(54, 13);
			this->timeLimitLabel->TabIndex = 8;
			this->timeLimitLabel->Text = L"Time Limit";
			// 
			// timeLimitComboBox
			// 
			this->timeLimitComboBox->FormattingEnabled = true;
			this->timeLimitComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(6) {
				L"No Limit", L"1 Second", L"2 Seconds",
					L"3 Seconds", L"4 Seconds", L"5 Seconds"
			});
			this->timeLimitComboBox->Location = System::Drawing::Point(118, 118);
			this->timeLimitComboBox->Name = L"timeLimitComboBox";
			this->timeLimitComboBox->Size = System::Drawing::Size(91, 21);
			this->timeLimitComboBox->TabIndex = 7;
			this->timeLimitComboBox->Text = L"No Limit";
			this->timeLimitComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::timeLimitComboBox_SelectedIndexChanged);

			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1320, 560);
			this->Controls->Add(this->player1Panel);
			this->Controls->Add(this->player2Panel);
			this->Controls->Add(this->controlPanel);

			this->Controls->Add(this->verticalLabel);
			this->Controls->Add(this->horizontalLabel);
			this->Controls->Add(this->horizontalLabel2);

			this->Name = L"MyForm";
			this->Text = L"Battleship";

			this->player2Panel->ResumeLayout(false);
			this->controlPanel->ResumeLayout(false);
			this->controlPanel->ResumeLayout(false);
			this->player1Box->ResumeLayout(false);
			this->player1Box->PerformLayout();
			this->controlBox->ResumeLayout(false);
			this->controlBox->PerformLayout();
			this->player2Box->ResumeLayout(false);
			this->player2Box->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();


		}
#pragma endregion
	private: System::Void player1Button_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void player2Button_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void player1HumanButton_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void player1PCButton_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void player1ConsoleCheckbox_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void player2HumanButton_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void player2PCButton_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void player2ConsoleCheckbox_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void resetButton_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void placeButton_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void showShipsCheckbox_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void playButton_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void timeLimitComboBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
	};
}
// update button appearance

