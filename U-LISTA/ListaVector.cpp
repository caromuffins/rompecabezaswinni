//---------------------------------------------------------------------------

#pragma hdrstop

#include "ListaVector.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

Lista::Lista()
{
	longitud = 0;
}

int Lista::fin()
{
	return longitud - 1;
}

int Lista::primero()
{
	return 0 - (longitud == 0);
}

int Lista::siguiente(int dir)
{
	dir++;
	if (dir == longitud || dir == 0)
		return NULOV;

	return dir;
}

int Lista::anterior(int dir)
{
	if (dir == NULOV)
		return NULOV;

	return dir - 1;
}

bool Lista::vacia()
{
	return (longitud == 0);
}

ElemL Lista::recupera(int dir)
{
	if (vacia())
		throw Exception("Lista Vacia");

	if (!(dir >= 0 && dir < longitud))
		throw Exception("ERROR: Direccion Fuera De Rango");

	return elementos[dir];
}

int Lista::LONGITUD()
{
	return longitud;
}

void Lista::inserta(int dir, ElemL elem)
{
	if (longitud == MAXV)
		throw Exception("Lista Llena");

	if (!(dir >= NULOV && dir < longitud))
		throw Exception("ERROR: Direccion fuera de rango");

	if (dir == NULOV)
		dir++;

	for (int i = longitud; i >= (dir + 1); i--)
		elementos[i] = elementos[i-1];

	elementos[dir] = elem;
	longitud++;
}

void Lista::inserta_primero(ElemL elem)
{
	if (longitud == MAXV)
		throw Exception("Lista Llena");

	for (int i = longitud; i >= 1; i--)
		elementos[i] = elementos[i-1];

	elementos[0] = elem;
	longitud++;
}

void Lista::inserta_ultimo(ElemL elem)
{
	if (longitud == MAXV)
		throw Exception("Lista Llena");

	elementos[longitud] = elem;
	longitud++;
}

void Lista::suprime(int dir)
{
	if (vacia())
		throw Exception("Lista Vacia");

	if (!(dir >= 0 && dir < longitud))
		throw Exception("ERROR: Direccion Fuera De Rango");

	longitud--;
	for (int i = dir; i < longitud; i++)
		elementos[i] = elementos[i+1];
}

void Lista::modifica(int dir, ElemL elem)
{
	if (longitud == 0)
		throw Exception("Lista Vacia");

	if (!(dir >= 0 && dir < longitud))
		throw Exception("ERROR: Direccion Fuera De Rango");

	elementos[dir] = elem;
}

int Lista::localiza(ElemL elem)
{
	int dir = primero();
	while (dir != NULOV) {
			if (recupera(dir) == elem)
				return dir;

			dir = siguiente(dir);
	}
	return NULOV;
}

void Lista::eliminaDato(ElemL elem)
{
	if (!vacia()) {
		int x = localiza(elem);
		while (x != NULOV) {
			suprime(x);
			x = localiza(elem);
		}
	}
	else
		throw Exception("Lista Vacia");
}

void Lista::anula()
{
	longitud = 0;
}

void Lista::mostrar(int posX, int posY)
{
	//const int posX = 400, posY = 10;

	TC->Font->Size = 16;
	TC->Font->Color = clRed;
	TC->Font->Style = TFontStyles() << fsBold;
	TC->Pen->Width = 1;
	TC->Pen->Color = clBlack;

	int h = TC->TextHeight("0");
	static int antSize = 0;
	TC->Brush->Color = clClear;
	TC->FillRect(Rect(posX, posY, posX + antSize, posY + h));

	TC->Brush->Style = bsClear;
	AnsiString list = "<";
	for (int i = 0; i < longitud; i++) {
		list += " " + FloatToStr(elementos[i]);
		if (i != longitud - 1) list += ",";
	}
	list += " >";
	antSize = TC->TextWidth(list) + 1;
	TC->TextOut(posX, posY, list);
}

void Lista::mostrarATR(int posX, int posY)
{
	TC->Font->Size = 14;
	int h = TC->TextHeight("0");
	static int antSize = 0;
	TC->Brush->Color = clClear;
	TC->FillRect(Rect(posX, posY, posX + antSize, posY + h*2 + 5));

	AnsiString atr1, atr2;
	atr1 = "elementos[]:";
	for (int i = 0; i < longitud; i++) {
		atr1 += " [" + FloatToStr(elementos[i]) + "]";
		if (i != longitud - 1) atr1 += ",";
	}
	atr2 = "longitud: " + IntToStr(longitud);
	antSize = TC->TextWidth(atr1);
	TC->TextOut(posX, posY, atr1);
	TC->TextOut(posX, posY + 5 + h, atr2);
}
