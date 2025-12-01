//---------------------------------------------------------------------------

#ifndef FormInstruccionesH
#define FormInstruccionesH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------

class TFormInstrucciones : public TForm
{
__published:	// IDE-managed Components
	TPanel *PanelMain;
	TLabel *LabelTitulo;
	TLabel *LabelJugador1;
	TLabel *LabelControles1;
	TLabel *LabelDeshacer1;
	TLabel *LabelJugador2;
	TLabel *LabelControles2;
	TLabel *LabelDeshacer2;
	TLabel *LabelObjetivo;
	TButton *ButtonComenzar;
	void __fastcall ButtonComenzarClick(TObject *Sender);

private:	// User declarations

public:		// User declarations
	__fastcall TFormInstrucciones(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormInstrucciones *FormInstrucciones;
//---------------------------------------------------------------------------
#endif
