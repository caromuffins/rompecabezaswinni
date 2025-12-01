//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormInstrucciones.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormInstrucciones *FormInstrucciones;
//---------------------------------------------------------------------------
__fastcall TFormInstrucciones::TFormInstrucciones(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormInstrucciones::ButtonComenzarClick(TObject *Sender)
{
	// Cerrar este dialogo
	ModalResult = mrOk;
	
	// Ocultar el menu principal
	Application->MainForm->Hide();
	
	// Mostrar Form1 (pantalla de juego)
	Form1->Show();
}
//---------------------------------------------------------------------------
