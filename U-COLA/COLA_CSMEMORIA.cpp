//---------------------------------------------------------------------------

#pragma hdrstop

#include "COLA_CSMEMORIA.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

Cola::Cola()
{
	ini = NULO;
	fin = NULO;
}

bool Cola::vacia()
{
	return (ini == NULO);
}

void Cola::poner(int e)
{
	int aux = M->new_espacio("elemento,sig");
	if (aux != NULO) {
		M->poner_dato(aux,"->elemento",e);
		M->poner_dato(aux,"->sig",NULO);
		if (ini == NULO)
			ini = aux;
		else
			M->poner_dato(fin,"->sig",aux);
		fin = aux;
	} else
		throw Exception("ERROR: NO HAY ESPACIO DISPONIBLE");
}

void Cola::sacar(int &e)
{
	if (ini == NULO)
		throw Exception("ERROR: Cola vacia");
	else {
		e = M->obtener_dato(ini,"->elemento");
		int x = ini;
		ini = M->obtener_dato(ini,"->sig");
		M->delete_espacio(x);
	}
}

int Cola::primero()
{
	if (ini == NULO)
		throw Exception("ERROR: Cola VACIA");
	else
		return M->obtener_dato(ini,"->elemento");
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
	int aux = ini;
	int e;
	while (aux != NULO) {
		e = M->obtener_dato(aux, "->elemento");
		cad += FloatToStr(e);
		aux = M->obtener_dato(aux, "->sig");
		if (aux != NULO) cad += ", ";
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
	TC->Font->Size = 10;
	int h = TC->TextHeight("0");
	int sElem = TC->TextWidth("0elemento0");
	int sSig = TC->TextWidth("0sig0");
	static int antWidth = 0;
	static int antHeight = 0;
	TC->Brush->Color = clClear;
	TC->FillRect(Rect(posX, posY, posX + antWidth, posY + antHeight));

	AnsiString strIni, strFin;
	strIni = "INI: " + IntToStr(ini);
	strFin = "FIN: " + IntToStr(fin);
	TC->TextOut(posX, posY, strIni + " | " + strFin);
	posY += h + 10;
	posX += 10;

	SetTextAlign(TC->Handle, TA_CENTER);
	int dir = ini;
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

	antWidth = posX + sElem + sSig + 2;
	antHeight = posY + h + 2;
}
