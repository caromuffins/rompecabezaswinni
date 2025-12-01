//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
TCanvas *TC;
TColor clClear;

CSMemoria *M = new CSMemoria();
ColaPri QP;
Rompecabezas R1;
Rompecabezas R2;
//---------------------------------------------------------------------------
void Desarmar()
{
	R1.IniciarJuego();
	R2.IniciarJuego();
	int n = rand();
	while (n > 0) {
		int a = rand() % 4;
		R1.MoverZ(a, false);
		R2.MoverZ(a, false);
		n--;
	}
}

void EjecutarMovimiento()
{
	int key;
	QP.sacar(key);
	switch (key) {
	case 'a': R1.MoverZ(0); break;
	case 'w': R1.MoverZ(1); break;
	case 'd': R1.MoverZ(2); break;
	case 's': R1.MoverZ(3); break;
	case VK_LEFT: R2.MoverZ(0); break;
	case VK_UP: R2.MoverZ(1); break;
	case VK_RIGHT: R2.MoverZ(2); break;
	case VK_DOWN: R2.MoverZ(3); break;
	default:
		break;
	}
}

__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	TC = Form1->Canvas;
	clClear = Form1->Color;

	WindowState = wsMaximized;

	Timer1->Interval = 500;
	Timer1->Enabled = false;
}
//---------------------------------------------------------------------------
//------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
	if (!QP.vacia()) {
		EjecutarMovimiento();
	} else
		Timer1->Enabled = false;

    if (R1.Solucionado()) {
		Timer1->Enabled = false;
		ShowMessage("Jugador 1 GANA");
	} else if (R2.Solucionado()) {
		Timer1->Enabled = false;
		ShowMessage("Jugador 2 GANA");
	}

	Pintar();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	WORD key = Key;
	Key |= 0x20;
	if (Key == 'w' || Key == 'a' || Key == 's' || Key == 'd') {
		QP.poner(Key, 0);
		QP.mostrar(500, 10);
	}
	else if (Key == VK_UP || Key == VK_LEFT || Key == VK_DOWN || Key == VK_RIGHT) {
		QP.poner(Key, 1);
        QP.mostrar(500, 10);
	}
	else if (Shift.Contains(ssCtrl) && Key == 'z')
		//QP.poner(Key, 0);
		R1.Retroceder();
	else if (key == VK_OEM_MINUS)
		//QP.poner(Key, 1);
		R2.Retroceder();
	else if (key == VK_RETURN) {
		Desarmar();
		Pintar();
	}

	Timer1->Enabled = true;
}
//---------------------------------------------------------------------------
void TForm1::Pintar()
{
	Repaint();
	int x1 = Form1->Width / 6;
	int x2 = Form1->Width / 2;
	int y = Form1->Height / 5;
	R1.Dibujar(x1, y);
	R2.Dibujar(x2, y);

    QP.mostrar(500, 10);

	Canvas->Font->Size = 25;
	int alto = Canvas->TextHeight("0");
	int ancho = alto;
	y *= 4;
	x1 += ancho * 2;
	x2 += ancho * 2;
	Canvas->Brush->Color = clSilver;
	Canvas->Rectangle(x1 + ancho, y - alto, x1 + ancho * 2, y);
	Canvas->Rectangle(x1, y, x1 + ancho, y + alto);
	Canvas->Rectangle(x1 + ancho, y, x1 + ancho * 2, y + alto);
	Canvas->Rectangle(x1 + ancho * 2, y, x1 + ancho * 3, y + alto);
	Canvas->Rectangle(x2 + ancho, y - alto, x2 + ancho * 2, y);
	Canvas->Rectangle(x2, y, x2 + ancho, y + alto);
	Canvas->Rectangle(x2 + ancho, y, x2 + ancho * 2, y + alto);
	Canvas->Rectangle(x2 + ancho * 2, y, x2 + ancho * 3, y + alto);

	int m = ancho / 2;
	SetTextAlign(TC->Handle, TA_CENTER);
	Canvas->Brush->Style = bsClear;
	Canvas->TextOut(x1 + ancho + m, y - alto, "W");
	Canvas->TextOut(x1 + m, y, "A");
	Canvas->TextOut(x1 + ancho + m, y, "S");
	Canvas->TextOut(x1 + ancho * 2 + m, y, "D");

	Canvas->TextOut(x2 + ancho + m, y - alto, L"\u2191");
	Canvas->TextOut(x2 + m, y, L"\u2190");
	Canvas->TextOut(x2 + ancho + m, y, L"\u2193");
	Canvas->TextOut(x2 + ancho * 2 + m, y, L"\u2192");
	SetTextAlign(TC->Handle, TA_LEFT);
}
