//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("Unit1.cpp", Form1);
USEFORM("FormMenu.cpp", FormMenu);
USEFORM("FormInstrucciones.cpp", FormInstrucciones);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		// Primero muestra FormMenu como formulario principal
		Application->CreateForm(__classid(TFormMenu), &FormMenu);
		// Form1 se crea pero no se muestra hasta presionar "Iniciar Juego"
		Application->CreateForm(__classid(TForm1), &Form1);
		// FormInstrucciones se crea para mostrar como dialogo
		Application->CreateForm(__classid(TFormInstrucciones), &FormInstrucciones);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
