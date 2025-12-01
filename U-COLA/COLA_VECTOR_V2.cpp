//---------------------------------------------------------------------------

#pragma hdrstop

#include "COLA_VECTOR_V2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

void Cola::desplazar(int d)
{
	for (int i = 0; i <= fin; i++) {
		if (i != MAX-1)
			V[i] = V[i+d];
	}
}

//---------------------------------------------------------------------------
Cola::Cola()
{
	fin = NULO;
	ini = 0;
}

bool Cola::vacia()
{
	return (ini > fin);
}

void Cola::poner(ElemQ e)
{
	if (fin < MAX) {
		fin++;
		V[fin] = e;
	} else
		throw Exception("ERROR: NO HAY ESPACIO DISPONIBLE");
}

void Cola::sacar(ElemQ &e)
{
	if (!(ini > fin)) {
		e = V[0];
		desplazar(1);
		fin--;
	}
	else
		throw Exception("ERROR: Cola vacia");
}

ElemQ Cola::primero()
{
	if (!(ini > fin))
        return V[0];
	else
		throw Exception("ERROR: Cola vacia");
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
	ElemQ e;
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
	TC->Font->Size = 14;
	int h = TC->TextHeight("0");
	static int antSize = 0;
	TC->Brush->Color = clClear;
	TC->FillRect(Rect(posX, posY, posX + antSize, posY + h*3.4));

	AnsiString atr1, atr2, atr3;
	atr1 = "V: [";
	for (int i = 0; i <= fin; i++) {
		atr1 += FloatToStr(V[i]);
		if (i != fin) atr1 += ", ";
	}
	atr1 += "]";
	atr2 = "Ini: " + IntToStr(ini);
	atr3 = "Fin: " + IntToStr(fin);
	antSize = TC->TextWidth(atr1);
    if (antSize < TC->TextWidth(atr3))
		antSize = TC->TextWidth(atr3);
	TC->TextOut(posX, posY, atr1);
	TC->TextOut(posX, posY + h * 1.2, atr2);
	TC->TextOut(posX, posY + h * 2.2, atr3);
}
