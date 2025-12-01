//---------------------------------------------------------------------------

#pragma hdrstop

#include "PILA_LISTA.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

bool Pila::vacia()
{
	return L.vacia();
}

void Pila::meter(int e)
{
	 L.inserta(L.primero(), e);
}

void Pila::sacar(int &e)
{
	e = L.recupera(L.primero());
	L.suprime(L.primero());
}

int Pila::cima()
{
	return L.recupera(L.primero());
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
	L.mostrar(posX, posY);
	L.mostrarATR(posX, posY + 25);
}
