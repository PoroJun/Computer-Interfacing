#pragma once

namespace Lab2COMINT {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

#pragma region DLL Imports
	using namespace System::Runtime::InteropServices;

	[DllImport("inpout32.dll", CharSet=CharSet::Ansi, EntryPoint="Inp32")]
	extern "C" short _stdcall Inp32(short PortAddress);

	[DllImport("inpout32.dll", CharSet = CharSet::Ansi, EntryPoint = "Out32")]
	extern "C" void _stdcall Out32(short PortAddress, short data);
#pragma endregion
	/// <summary>
	/// Summary for main
	/// </summary>
	public ref class main : public System::Windows::Forms::Form
	{
	public:
		main(void)
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
		~main()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:

	private: System::Windows::Forms::Button^  btnSmoke;
	private: System::Windows::Forms::Label^  lblSmoke;
	private: System::Windows::Forms::Timer^  timerSmoke;
	private: System::Windows::Forms::TextBox^  txtSmoke;

	private: System::ComponentModel::IContainer^  components;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->btnSmoke = (gcnew System::Windows::Forms::Button());
			this->lblSmoke = (gcnew System::Windows::Forms::Label());
			this->timerSmoke = (gcnew System::Windows::Forms::Timer(this->components));
			this->txtSmoke = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// btnSmoke
			// 
			this->btnSmoke->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->btnSmoke->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnSmoke->Location = System::Drawing::Point(138, 12);
			this->btnSmoke->Name = L"btnSmoke";
			this->btnSmoke->Size = System::Drawing::Size(112, 30);
			this->btnSmoke->TabIndex = 2;
			this->btnSmoke->Text = L"Smoke Alarm";
			this->btnSmoke->UseVisualStyleBackColor = true;
			this->btnSmoke->Click += gcnew System::EventHandler(this, &main::btnSmoke_Click);
			// 
			// lblSmoke
			// 
			this->lblSmoke->AutoSize = true;
			this->lblSmoke->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblSmoke->Location = System::Drawing::Point(19, 18);
			this->lblSmoke->Name = L"lblSmoke";
			this->lblSmoke->Size = System::Drawing::Size(73, 17);
			this->lblSmoke->TabIndex = 3;
			this->lblSmoke->Text = L"lblSmoke";
			// 
			// timerSmoke
			// 
			this->timerSmoke->Interval = 200;
			this->timerSmoke->Tick += gcnew System::EventHandler(this, &main::timerSmoke_Tick);
			// 
			// txtSmoke
			// 
			this->txtSmoke->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->txtSmoke->Location = System::Drawing::Point(12, 48);
			this->txtSmoke->Name = L"txtSmoke";
			this->txtSmoke->ReadOnly = true;
			this->txtSmoke->Size = System::Drawing::Size(235, 20);
			this->txtSmoke->TabIndex = 4;
			// 
			// main
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Gainsboro;
			this->ClientSize = System::Drawing::Size(262, 83);
			this->Controls->Add(this->txtSmoke);
			this->Controls->Add(this->lblSmoke);
			this->Controls->Add(this->btnSmoke);
			this->Name = L"main";
			this->Text = L"Lab 2 - Parallel Port";
			this->Load += gcnew System::EventHandler(this, &main::main_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void main_Load(System::Object^  sender, System::EventArgs^  e) {
		Out32(0x37a,0x00);
		timerSmoke->Enabled = true;
		this->Text = "Parallel Port";\
		lblSmoke->Text = "Detector: Off";
		txtSmoke->Text = "Sensor is Off";
	}
	private: System::Void btnSmoke_Click(System::Object^  sender, System::EventArgs^  e) {
		static int count = 0;
		if (count % 2 == 0) {
			lblSmoke->Text = "Detector: On";
			txtSmoke->Text = "Sensor is Normal";
		}
		else {
			lblSmoke->Text = "Detector: Off";
			txtSmoke->Text = "Sensor is Off";
		}

		count++;
	}
	private: System::Void timerSmoke_Tick(System::Object^  sender, System::EventArgs^  e) {
		unsigned char status_read;

		status_read = (unsigned char)Inp32(0x379);
		status_read >>= 3;
		status_read &= 0x01;

		if (status_read == 0x00) {
			if (lblSmoke->Text == "Detector: On") {
				Out32(0x378, 0x03);
				txtSmoke->Text = "Sensor is Triggered";
			}
		}
		else {
			if (lblSmoke->Text == "Detector: On") {
				Out32(0x378, 0x00);
				txtSmoke->Text = "Sensor is Normal";
			}
		}
	}


	private: System::Void lblSwitch_Click(System::Object^  sender, System::EventArgs^  e) {

	}
};
}
