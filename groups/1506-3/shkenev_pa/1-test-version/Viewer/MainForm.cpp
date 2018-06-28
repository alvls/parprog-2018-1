#include "MainForm.h"

[STAThreadAttribute]
int __clrcall WinMain(array<System::String ^> ^args)
{
	if (args->Length == 2 && File::Exists(args[0]))
		Viewer::readData(args[0])->Save(args[1], System::Drawing::Imaging::ImageFormat::Png);
	else
	{
		// Enabling Windows XP visual effects before any controls are created
		System::Windows::Forms::Application::EnableVisualStyles();
		System::Windows::Forms::Application::SetCompatibleTextRenderingDefault(false); 

		// Create the main window and run it
		System::Windows::Forms::Application::Run(gcnew Viewer::MainForm());
	}

	return 0;
}

Bitmap ^Viewer::readData(String ^fileName)
{
	BinaryReader ^br = gcnew BinaryReader(File::Open(fileName, FileMode::Open));
	int width = br->ReadInt32();
	int height = br->ReadInt32();

	Bitmap ^bitmap = gcnew Bitmap(width, height);
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
			bitmap->SetPixel(i, j, Color::FromArgb(br->ReadByte(), br->ReadByte(), br->ReadByte()));
	}

	br->Close();
	return bitmap;
}
