//---------------------------------------------------------------------------

#pragma hdrstop

#include "PILA_STRING.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

Pila::Pila()
{
	P = "";
}

bool Pila::vacia()
{
	return P == "";
}

void Pila::meter(int e)
{
	if (P != "")
		P = "," + P;
	P = to_string(e) + P;
}

void Pila::sacar(int &e)
{
	if (P == "")
		throw Exception("ERROR: PILA VACIA");

	int pos = P.find(',');
	if (pos < 0) {
		e = stof(P);
		P.clear();
	} else {
		e = stof(P.substr(0, pos));
		P.erase(0, pos+1);
	}
}

int Pila::cima()
{
    if (P == "")
		throw Exception("ERROR: PILA VACIA");

	int pos = P.find(',');
	if (pos < 0)
		return stof(P);
	else
		return stof(P.substr(0, pos));
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
	TC->FillRect(Rect(posX, posY, posX + antSize, posY + h * 2 + 5));

	antSize = TC->TextWidth(P.c_str());
	TC->TextOut(posX, posY, P.c_str());
}
