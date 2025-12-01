//---------------------------------------------------------------------------

#pragma hdrstop

#include "COLA_LISTA.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

bool Cola::vacia()
{
	return L.vacia();
}

void Cola::poner(int e)
{
	 L.inserta(L.primero(), e);
}

void Cola::sacar(int &e)
{
	e = L.recupera(L.fin());
	L.suprime(L.fin());
}

int Cola::primero()
{
	return L.recupera(L.fin());
}

void Cola::mostrar(int x, int y, TColor fondo)
{
	TC->Font->Size = 16;
	TC->Font->Color = clBlack;
	TC->Pen->Width = 1;
	TC->Pen->Color = clBlack;

    int w = TC->TextWidth("0, 0");
	int h = TC->TextHeight("0");
	int m = w >> 1;

	static int antSize = 0;
	TC->Brush->Color = clClear;
	TC->FillRect(Rect(x, y, x + antSize + w, y + h + 1));

	AnsiString cad = "";
	Cola aux;
	int e;
	while (!vacia()) {
		sacar(e);
		aux.poner(e);
	}
	while (!aux.vacia()) {
		aux.sacar(e);
		poner(e);
		cad += FloatToStr(e);
        if (!aux.vacia()) cad += ", ";
	}

	TC->Brush->Color = fondo;
	TC->Pie(x, y, x + w, y + h, x + m, y - h, x + m, y + h);
	antSize = TC->TextWidth(cad) + w;
	TC->FillRect(Rect(x + m, y, x + antSize, y + h));
	TC->Brush->Color = clClear;
	TC->Pie(x + antSize - m, y, x + antSize + m, y + h, x + antSize, y - h, x + antSize, y + h);
	TC->MoveTo(x + m, y);
	TC->LineTo(x + antSize - 1, y);
	TC->Pen->Color = clClear;
	TC->LineTo(x + antSize - 1, y + h - 1);
	TC->Pen->Color = clBlack;
	TC->LineTo(x + m - 1, y + h - 1);
	TC->Brush->Style = bsClear;
	TC->TextOut(x + m * 0.8, y, cad);
}

void Cola::mostrarATR(int posX, int posY)
{
	L.mostrar(posX, posY);
	L.mostrarATR(posX, posY + 25);
}
