//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <ctime>  // Para time()
#include "Unit1.h"
#include "FormMenu.h"
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
	srand(time(NULL));  // Inicializar semilla aleatoria
	int n = 50 + rand() % 51;  // Entre 50 y 100 movimientos
	for (int i = 0; i < n; i++) {
		int a = rand() % 4;
		R1.MoverZ(a, false);
		R2.MoverZ(a, false);
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
void TForm1::MostrarGanador(int jugador)
{
	// Deshabilitar timer inmediatamente
	Timer1->Enabled = false;
	
	// Cambiar color de fondo con colores pastel
	if (jugador == 1) {
		Color = TColor(0xE6E6FA);  // Lavanda pastel
		LabelGanador->Caption = L"¡JUGADOR 1 GANA!";
		LabelGanador->Font->Color = TColor(0x8B008B);  // Púrpura oscuro (contraste)
	} else {
		Color = TColor(0xFFB6C1);  // Rosa pastel
		LabelGanador->Caption = L"¡JUGADOR 2 GANA!";
		LabelGanador->Font->Color = TColor(0xC71585);  // Rosa oscuro (contraste)
	}
	
	// Mostrar label del ganador
	LabelGanador->Visible = true;
	LabelGanador->BringToFront();
	
	// Mostrar boton para jugar de nuevo
	ButtonJugarDeNuevo->Visible = true;
	ButtonJugarDeNuevo->BringToFront();
	
	// Ocultar otros elementos
	LabelJugador1->Visible = false;
	LabelJugador2->Visible = false;
	ButtonDesordenar->Visible = false;
}
//---------------------------------------------------------------------------
void TForm1::OcultarGanador()
{
	// Restaurar color de fondo
	Color = clBtnFace;
	
	// Ocultar label del ganador
	LabelGanador->Visible = false;
	ButtonJugarDeNuevo->Visible = false;
	
	// Mostrar otros elementos
	LabelJugador1->Visible = true;
	LabelJugador2->Visible = true;
	ButtonDesordenar->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonDesordenarClick(TObject *Sender)
{
	Desarmar();
	Pintar();
	this->SetFocus(); // Devolver foco al formulario
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonVolverMenuClick(TObject *Sender)
{
	// Ocultar Form1 y mostrar el menu principal
	Hide();
	OcultarGanador();
	R1.IniciarJuego();
	R2.IniciarJuego();
	FormMenu->Show();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonJugarDeNuevoClick(TObject *Sender)
{
	// Reiniciar el juego
	OcultarGanador();
	R1.IniciarJuego();
	R2.IniciarJuego();
	Desarmar();
	Pintar();
	this->SetFocus(); // Devolver foco al formulario
}
//------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
	if (!QP.vacia()) {
		EjecutarMovimiento();
	} else
		Timer1->Enabled = false;

    if (R1.Solucionado()) {
		Timer1->Enabled = false;
		MostrarGanador(1);
	} else if (R2.Solucionado()) {
		Timer1->Enabled = false;
		MostrarGanador(2);
	}

	Pintar();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	// No procesar teclas si se muestra el ganador
	if (LabelGanador->Visible)
		return;

	WORD key = Key;
	
	// Procesar teclas de flecha para Jugador 2 ANTES de cualquier otra cosa
	if (key == VK_UP || key == VK_LEFT || key == VK_DOWN || key == VK_RIGHT) {
		QP.poner(key, 1);
		QP.mostrar(500, 10);
		Timer1->Enabled = true;
		Key = 0; // Consumir la tecla para evitar navegación de botones
		return;
	}
	
	// Convertir a minúscula solo para teclas alfabéticas WASD
	if (key == 'W' || key == 'w' || key == 'A' || key == 'a' ||
		key == 'S' || key == 's' || key == 'D' || key == 'd') {
		WORD keyLower = key | 0x20;
		QP.poner(keyLower, 0);
		QP.mostrar(500, 10);
		Timer1->Enabled = true;
		return;
	}
	
	// Retroceder movimientos
	if (Shift.Contains(ssCtrl) && (key == 'Z' || key == 'z')) {
		R1.Retroceder();
		Timer1->Enabled = true;
	} else if (key == VK_OEM_MINUS) {
		R2.Retroceder();
		Timer1->Enabled = true;
	}
}
//---------------------------------------------------------------------------
void TForm1::Pintar()
{
	// No pintar si se muestra el ganador
	if (LabelGanador->Visible)
		return;

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
	Canvas->Brush->Color = TColor(0xE6E6FA);  // Lavanda pastel para ambos teclados
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
