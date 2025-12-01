//---------------------------------------------------------------------------

#pragma hdrstop

#include "PILA_PUNTERO.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

Pila::Pila()
{
	tope = nullptr;
}

void Pila::crear()
{
	tope = nullptr;
}

bool Pila::vacia()
{
	return (tope == nullptr);
}

void Pila::meter(int e)
{
	NodoS* x = new NodoS;
	if (x != nullptr) {
		x->elemento = e;
		x->sig = tope;
		tope = x;
	} else
		throw Exception("ERROR: NO HAY ESPACIO EN MEMORIA");
}

void Pila::sacar(int &e)
{
	if (vacia())
		throw Exception("ERROR: PILA VACIA");

	else {
		NodoS* aux = tope;
		e = tope->elemento;
		tope = tope->sig;
		delete aux;
	}
}

int Pila::cima()
{
	if (vacia())
		throw Exception("ERROR: PILA VACIA");
	else
		return tope->elemento;
}

void Pila::mostrar(int posX, int posY)
{
	//const int posX = 300, posY = 400;

	TC->Font->Size = 12;
	TC->Font->Color = clBlack;
	TC->Pen->Width = 1;
	TC->Pen->Color = clBlack;

	int w = TC->TextWidth("12345678");
	int h = TC->TextHeight("0");
	int m = w * 0.5;

	static int antSize = 0;
	TC->Brush->Color = clClear;
	TC->FillRect(Rect(posX, posY + h, posX + w + 1, posY - antSize));

	SetTextAlign(TC->Handle, TA_CENTER);
	TC->Brush->Color = clLime;
	TC->Rectangle(posX, posY, posX + w, posY + h);
	TC->Brush->Style = bsClear;
	TC->TextOut(posX + m, posY, "usuario");

	Pila aux;
	int e, i = 0;
	while (!vacia()) {
		sacar(e);
		aux.meter(e);
		i++;
	}
	antSize = i * h + 1;
	i = 0;
	while (!aux.vacia()) {
		aux.sacar(e);
		TC->Brush->Color = clYellow;
		TC->Rectangle(posX, posY - h * (i + 1), posX + w, posY - h * i);
		TC->Brush->Style = bsClear;
		TC->TextOut(posX + m, posY - h * (i + 1), e);
		meter(e);
		i++;
	}

	SetTextAlign(TC->Handle, TA_LEFT);
}

void Pila::mostrarATR(int posX, int posY)
{
	TC->Font->Size = 14;
	int h = TC->TextHeight("0");
	static int antSize = 0;
	TC->Brush->Color = clClear;
	TC->FillRect(Rect(posX, posY, posX + antSize, posY + h));

	AnsiString atr1;
	atr1 = "Tope: " + IntToStr(int(tope));
	antSize = TC->TextWidth(atr1);
	TC->TextOut(posX, posY, atr1);
}
