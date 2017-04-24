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
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	protected:
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  optionsToolStripMenuItem;
	private: System::Windows::Forms::Panel^  player2Panel;
	private: System::Windows::Forms::Panel^  player1Panel;
	private: System::Windows::Forms::Panel^  controlPanel;
	private: System::Windows::Forms::Label^  verticalLabel;
	private: System::Windows::Forms::Label^  horizontalLabel;
	private: System::Windows::Forms::Label^  horizontalLabel2;
			 const int BOARD_SIZE = 20;
	public: array<System::Windows::Forms::Button^, 2>^ player1Buttons = gcnew array<System::Windows::Forms::Button^, 2>(BOARD_SIZE, BOARD_SIZE);
	public: array<System::Windows::Forms::Button^, 2>^ player2Buttons = gcnew array<System::Windows::Forms::Button^, 2>(BOARD_SIZE, BOARD_SIZE);


	public:

	private:


	private:
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

			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->optionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->player2Panel = (gcnew System::Windows::Forms::Panel());
			this->controlPanel = (gcnew System::Windows::Forms::Panel());
			this->verticalLabel = (gcnew System::Windows::Forms::Label());
			this->horizontalLabel = (gcnew System::Windows::Forms::Label());
			this->horizontalLabel2 = (gcnew System::Windows::Forms::Label());

			// instantiate buttons
			for(int i = 0; i < BOARD_SIZE; i++)
			{
				for(int j = 0; j < BOARD_SIZE; j++)
				{
					this->player1Buttons[i, j] = (gcnew System::Windows::Forms::Button());
					this->player2Buttons[i, j] = (gcnew System::Windows::Forms::Button());
				}
			}



			this->player1Panel = (gcnew System::Windows::Forms::Panel());
			this->menuStrip1->SuspendLayout();
			this->player2Panel->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->fileToolStripMenuItem,
					this->optionsToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1289, 24);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// optionsToolStripMenuItem
			// 
			this->optionsToolStripMenuItem->Name = L"optionsToolStripMenuItem";
			this->optionsToolStripMenuItem->Size = System::Drawing::Size(61, 20);
			this->optionsToolStripMenuItem->Text = L"Options";
		
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

			//control panel
			this->controlPanel->Location = System::Drawing::Point(10, 50);
			this->controlPanel->Name = L"controlPanel";
			this->controlPanel->Size = System::Drawing::Size(250, 500);
			this->controlPanel->TabIndex = 2;
			this->controlPanel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;

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
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1320, 560);
			this->Controls->Add(this->player1Panel);
			this->Controls->Add(this->player2Panel);
			this->Controls->Add(this->controlPanel);
			this->Controls->Add(this->menuStrip1);
			this->Controls->Add(this->verticalLabel);
			this->Controls->Add(this->horizontalLabel);
			this->Controls->Add(this->horizontalLabel2);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->Text = L"Battleship";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->player2Panel->ResumeLayout(false);
			this->controlPanel->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();


		}
#pragma endregion
		private: System::Void player1Button_Click(System::Object^  sender, System::EventArgs^  e); 
		private: System::Void player2Button_Click(System::Object^  sender, System::EventArgs^  e);

	};
}
// update button appearance

