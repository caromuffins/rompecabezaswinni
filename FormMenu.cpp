//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormMenu.h"
#include "FormInstrucciones.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMenu *FormMenu;
//---------------------------------------------------------------------------
__fastcall TFormMenu::TFormMenu(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormMenu::FormCreate(TObject *Sender)
{
	// Centrar el formulario en la pantalla
	Position = poScreenCenter;
}
//---------------------------------------------------------------------------
void __fastcall TFormMenu::ButtonIniciarClick(TObject *Sender)
{
	// Mostrar ventana de instrucciones
	FormInstrucciones->ShowModal();
}
//---------------------------------------------------------------------------
