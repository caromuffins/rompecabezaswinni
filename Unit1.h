//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>

#include "UnitCSMemoria.h"
#include "Rompecabezas.h"
//---------------------------------------------------------------------------

class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TTimer *Timer1;
	TLabel *LabelJugador1;
	TLabel *LabelJugador2;
	TLabel *LabelGanador;
	TButton *ButtonDesordenar;
	TButton *ButtonVolverMenu;
	TButton *ButtonJugarDeNuevo;
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall ButtonDesordenarClick(TObject *Sender);
	void __fastcall ButtonVolverMenuClick(TObject *Sender);
	void __fastcall ButtonJugarDeNuevoClick(TObject *Sender);

private:	// User declarations
	void MostrarGanador(int jugador);
	void OcultarGanador();

public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
    void Pintar();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
