//---------------------------------------------------------------------------

#pragma hdrstop

#include "PILA_CSMEMORIA.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

Pila::Pila()
{
	tope = NULO;
}

bool Pila::vacia()
{
	return (tope == NULO);
}

void Pila::meter(int e)
{
	int aux = M->new_espacio("elemento,sig");
	if (aux != NULO) {
		M->poner_dato(aux,"->elemento",e);
		M->poner_dato(aux,"->sig",tope);
		tope = aux;
	} else
		throw Exception("ERROR: NO HAY ESPACIO EN MEMORIA");
}

void Pila::sacar(int &e)
{
	if (vacia())
		throw Exception("ERROR: PILA VACIA");

	else {
		int aux = tope;
		e = M->obtener_dato(tope,"->elemento");
		tope = M->obtener_dato(tope,"->sig");
		M->delete_espacio(aux);
	}
}

int Pila::cima()
{
	if (vacia())
		throw Exception("ERROR: PILA VACIA");

	else
		return M->obtener_dato(tope,"->elemento");
}

void Pila::mostrar(int posX, int posY)
{
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
		TC->Brush->Color = clSkyBlue;
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
	TC->Font->Size = 10;
	int h = TC->TextHeight("0");
	int sElem = TC->TextWidth("0elemento0");
	int sSig = TC->TextWidth("0sig0");
	static int antSize = 0;
	TC->Brush->Color = clClear;
	TC->FillRect(Rect(posX, posY, posX + antSize, posY + h));

	AnsiString strTope;
	strTope = "Tope: " + IntToStr(tope);
	TC->TextOut(posX, posY, strTope);
	posY += h + 10;
	posX += 10;

	SetTextAlign(TC->Handle, TA_CENTER);
	int dir = tope;
	while (dir != NULO) {
		TC->Brush->Color = clSkyBlue;
		TC->Rectangle(posX, posY, posX + sElem, posY + h);
		TC->Rectangle(posX + sElem, posY, posX + sElem + sSig, posY + h);
		TC->Brush->Color = clGray;
		TC->Rectangle(posX, posY + h, posX + sElem, posY + h*2);
		TC->Rectangle(posX + sElem, posY + h, posX + sElem + sSig, posY + h*2);

		int sigDir = M->obtener_dato(dir, "->sig");
		TC->Brush->Style = bsClear;
		TC->TextOut(posX + sElem*0.5, posY, M->obtener_dato(dir, "->elemento"));
		TC->TextOut(posX + sElem + sSig*0.5, posY, sigDir);
		posY += h;
		TC->TextOut(posX + sElem*0.5, posY, "elemento");
		TC->TextOut(posX + sElem + sSig*0.5, posY, "sig");
		posX += 10;
		posY += h + 10;
		dir = sigDir;
	}
}
