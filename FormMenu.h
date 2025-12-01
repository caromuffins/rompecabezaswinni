//---------------------------------------------------------------------------

#ifndef FormMenuH
#define FormMenuH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------

class TFormMenu : public TForm
{
__published:	// IDE-managed Components
	TPanel *PanelMain;
	TLabel *LabelTitulo;
	TLabel *LabelSubtitulo;
	TButton *ButtonIniciar;
	void __fastcall ButtonIniciarClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);

private:	// User declarations

public:		// User declarations
	__fastcall TFormMenu(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMenu *FormMenu;
//---------------------------------------------------------------------------
#endif
