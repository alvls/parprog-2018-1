using namespace System;
using namespace System::IO;
using namespace System::Drawing;

void convertFromImageToBinary(String ^fileName, String ^fileNameOut);

// typer входной_файл выходной_файл
int main(array<System::String ^> ^args)
{
	String ^fileName; // Имя входного файла
	String ^fileNameOut; // Имя выходного файла

	if (args->Length > 0 && File::Exists(args[0])) // Верно указан входной файл
		fileName = args[0];
	else
	{
		using namespace System::Windows::Forms;
		OpenFileDialog ^openFileDialog = gcnew OpenFileDialog();
		openFileDialog->Filter = "Изображения|*.bmp;*.gif;*.jpg;*.png;*.tiff";
		openFileDialog->Title = "Выберите изображение для преобразования в двоичный файл";
		if (openFileDialog->ShowDialog() != DialogResult::OK)
		{
			System::Console::WriteLine("Файл не выбран! Выход из программы...");
			return 0;
		}
		fileName = openFileDialog->FileName;
	}
	
	if (args->Length > 1) // Указан выходной файл
		fileNameOut = args[1];
	else
		fileNameOut = fileName + ".bin";

	convertFromImageToBinary(fileName, fileNameOut);
	System::Console::WriteLine("Двоичный файл: " + fileNameOut + ".");
	return 0;
}

void convertFromImageToBinary(String ^fileName, String ^fileNameOut)
{
	Bitmap ^image = gcnew Bitmap(fileName); // Исходное изображение

	BinaryWriter ^bw = gcnew BinaryWriter(File::Open(fileNameOut, FileMode::Create));
	bw->Write(image->Width);
	bw->Write(image->Height);

	for (int j = 0; j < image->Height; j++)
	{
		for (int i = 0; i < image->Width; i++)
		{
			Color colour = image->GetPixel(i, j);
			bw->Write(colour.R);
			bw->Write(colour.G);
			bw->Write(colour.B);
		}
	}

	bw->Close();
}
