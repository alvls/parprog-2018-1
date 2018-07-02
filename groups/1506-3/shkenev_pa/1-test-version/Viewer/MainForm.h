#pragma once

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::IO;

namespace Viewer
{
	Bitmap ^readData(String ^fileName);

	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
		}

	protected:
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MainMenu^  mainMenu1;
	private: System::Windows::Forms::MenuItem^  menuItemOpen;
	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::MenuItem^  menuItemSave;

	private:
		Bitmap ^bitmap;
		String ^fileName;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->mainMenu1 = (gcnew System::Windows::Forms::MainMenu(this->components));
			this->menuItemOpen = (gcnew System::Windows::Forms::MenuItem());
			this->menuItemSave = (gcnew System::Windows::Forms::MenuItem());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// mainMenu1
			// 
			this->mainMenu1->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(2) {this->menuItemOpen, this->menuItemSave});
			// 
			// menuItemOpen
			// 
			this->menuItemOpen->Index = 0;
			this->menuItemOpen->Text = L"Открыть...";
			this->menuItemOpen->Click += gcnew System::EventHandler(this, &MainForm::menuItemOpen_Click);
			// 
			// menuItemSave
			// 
			this->menuItemSave->Enabled = false;
			this->menuItemSave->Index = 1;
			this->menuItemSave->Text = L"Сохранить";
			this->menuItemSave->Click += gcnew System::EventHandler(this, &MainForm::menuItemSave_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(292, 245);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(292, 245);
			this->Controls->Add(this->pictureBox1);
			this->Menu = this->mainMenu1;
			this->Name = L"MainForm";
			this->Text = L"Просмотр";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void menuItemOpen_Click(System::Object^  sender, System::EventArgs^  e)
			{
				OpenFileDialog ^dialog = gcnew OpenFileDialog();
				if (dialog->ShowDialog() == ::DialogResult::OK)
				{
					fileName = dialog->FileName;
					bitmap = readData(fileName);
					this->Width = bitmap->Width + 8;
					this->Height = bitmap->Height + 55;
					pictureBox1->Image = bitmap;
					menuItemSave->Enabled = true;
				}
			}

	private: System::Void menuItemSave_Click(System::Object^  sender, System::EventArgs^  e)
			{
				String ^outFileName = fileName + ".png";
				bitmap->Save(outFileName, System::Drawing::Imaging::ImageFormat::Png);
				menuItemSave->Enabled = false;
				MessageBox::Show("Сохранено в " + outFileName, "Сохранение");
			}

};
}
