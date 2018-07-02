using namespace System;
using namespace System::IO;
using namespace System::Drawing;

void convertFromImageToBinary(String ^fileName, String ^fileNameOut);

// typer �������_���� ��������_����
int main(array<System::String ^> ^args)
{
	String ^fileName; // ��� �������� �����
	String ^fileNameOut; // ��� ��������� �����

	if (args->Length > 0 && File::Exists(args[0])) // ����� ������ ������� ����
		fileName = args[0];
	else
	{
		using namespace System::Windows::Forms;
		OpenFileDialog ^openFileDialog = gcnew OpenFileDialog();
		openFileDialog->Filter = "�����������|*.bmp;*.gif;*.jpg;*.png;*.tiff";
		openFileDialog->Title = "�������� ����������� ��� �������������� � �������� ����";
		if (openFileDialog->ShowDialog() != DialogResult::OK)
		{
			System::Console::WriteLine("���� �� ������! ����� �� ���������...");
			return 0;
		}
		fileName = openFileDialog->FileName;
	}
	
	if (args->Length > 1) // ������ �������� ����
		fileNameOut = args[1];
	else
		fileNameOut = fileName + ".bin";

	convertFromImageToBinary(fileName, fileNameOut);
	System::Console::WriteLine("�������� ����: " + fileNameOut + ".");
	return 0;
}

void convertFromImageToBinary(String ^fileName, String ^fileNameOut)
{
	Bitmap ^image = gcnew Bitmap(fileName); // �������� �����������

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
