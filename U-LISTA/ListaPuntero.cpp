//---------------------------------------------------------------------------

#pragma hdrstop

#include "ListaPuntero.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

Lista::Lista()
{
	longitud = 0;
	ptrElementos = nullptr;
}

Nodo* Lista::fin()
{
	Nodo* dirFin = ptrElementos;
	if (dirFin != nullptr) {
		while (dirFin->sig != nullptr)
			dirFin = dirFin->sig;
	}
	return dirFin;
}

Nodo* Lista::primero()
{
	return ptrElementos;
}

Nodo* Lista::siguiente(Nodo* dir)
{
	if (dir == nullptr)
		return nullptr;

	return dir->sig;
}

Nodo* Lista::anterior(Nodo* dir)
{
	if (dir == ptrElementos || dir == nullptr)
		return nullptr;

	Nodo* ant = ptrElementos;
	while (ant->sig != dir)
		ant = ant->sig;

	return ant;
}

bool Lista::vacia()
{
	return (longitud == 0);
}

ElemL Lista::recupera(Nodo* dir)
{
	if (vacia())
		throw Exception("Lista Vacia");
	else
		return dir->elemento;
}

int Lista::LONGITUD()
{
	return longitud;
}

void Lista::inserta(Nodo* dir, ElemL elem)
{
	Nodo* x = new Nodo();
	if (x != nullptr) {
		x->elemento = elem;
		x->sig = dir;

		Nodo* ant = anterior(dir);
		if (ant == nullptr)
			ptrElementos = x;
		else
			ant->sig = x;

		longitud++;
	} else
		throw Exception("No existe espacio en memoria");
}

void Lista::inserta_primero(ElemL elem)
{
	Nodo* x = new Nodo;
	if (x != nullptr) {
		x->elemento = elem;
		x->sig = ptrElementos;
		ptrElementos = x;
		longitud++;
	} else
		throw Exception("No existe espacio en memoria");
}

void Lista::inserta_ultimo(ElemL elem)
{
	Nodo* x = new Nodo;
	if (x != nullptr) {
		x->elemento = elem;
		x->sig = nullptr;

		if (longitud != 0)
			fin()->sig = x;
		else
			ptrElementos = x;

		longitud++;
	} else
		throw Exception("No existe espacio en memoria");
}

void Lista::suprime(Nodo* dir)
{
	if (longitud == 0)
		throw Exception("Lista Vacia");

	if (dir == ptrElementos) {
		ptrElementos = ptrElementos->sig;
		delete dir;
	} else {
		Nodo* ant = anterior(dir);
		ant->sig = siguiente(dir);
		delete dir;
	}
	longitud--;
}

void Lista::modifica(Nodo* dir, ElemL elem)
{
	if (vacia())
		throw Exception("Lista Vacia");

	dir->elemento = elem;
}

Nodo* Lista::localiza(ElemL elem)
{
	Nodo* dir = primero();
	while (dir != nullptr) {
		if (recupera(dir) == elem)
			return dir;

		dir = dir->sig;
	}

	return nullptr;
}

void Lista::eliminaDato(ElemL elem)
{
	Nodo* x = localiza(elem);
	while (x != nullptr) {
		suprime(x);
		x = localiza(elem);
	}
}

void Lista::anula()
{
	while (!vacia())
		suprime(fin());
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
	Nodo* x = ptrElementos;
	while (x != nullptr) {
		ElemL e = x->elemento;
		list += " " + FloatToStr(e);
		x = x->sig;
		if (x != nullptr) list += ",";
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
	atr1 = "ptrElementos: " + IntToStr(int(ptrElementos));
	atr2 = "longitud: " + IntToStr(longitud);
	antSize = TC->TextWidth(atr1);
	TC->TextOut(posX, posY, atr1);
	TC->TextOut(posX, posY + 5 + h, atr2);
}
