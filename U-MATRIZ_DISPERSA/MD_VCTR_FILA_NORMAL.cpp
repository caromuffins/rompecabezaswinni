//---------------------------------------------------------------------------

#pragma hdrstop

#include "MD_VCTR_FILA_NORMAL.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//--------------------------------------------------------------------------

int MatrizDispersa::buscar(int f, int c)
{
	if (nt != 0) {
		for (int i = 0; i < nt; i++) {
			if ((VF[i] == f) && (VC[i] == c)) {
				return i;
			}
		}
	}

	return NULO;
}

void MatrizDispersa::desplazar(int lug)
{
	for (int i = lug; i < nt-1; i++) {
		VF[i] = VF[i+1];
		VC[i] = VC[i+1];
		VD[i] = VD[i+1];
	}
	nt--;
}

//---------------------------------------------------------------------------
MatrizDispersa::MatrizDispersa()
{
	dimF = 0;
	dimC = 0;
	rep = 0;
	nt = 0;
}

void MatrizDispersa::dimensionar(int nf, int nc)
{
	dimF = nf;
	dimC = nc;
}

int MatrizDispersa::dimension_fila()
{
	return dimF;
}

int MatrizDispersa::dimension_columna()
{
	return dimC;
}

void MatrizDispersa::poner(int f, int c, int valor)
{
	int lug = buscar(f,c);
	if (lug != NULO){
		VD[lug] = valor;
		if (VD[lug] == rep)
			desplazar(lug);
	} else {
		if (nt < MAX) {
			nt++;
			VD[nt-1] = valor;
			VF[nt-1] = f;
			VC[nt-1] = c;
		} else
			throw Exception("ERROR: No existe espacio");
	}
}

int MatrizDispersa::elemento(int f, int c)
{
	if (((f >= 1) && (f <= dimF)) && ((c >= 1) && (c <= dimC))) {
		int lug = buscar(f, c);
		if (lug != NULO)
			return VD[lug];

		else
			return rep;

	} else
		throw Exception("ERROR: Indices Fuera De Rango");
}

void MatrizDispersa::definir_valor_repetido(int valor)
{
	int i = 0;
	while (i < nt){
		if (VD[i] == valor)
			desplazar(i);
		else
			i++;
	}

	rep = valor;
}

void MatrizDispersa::mostrar(int iniFila, int iniCol, int ultFila, int ultCol, int X, int Y)
{
	TC->Font->Size = 16;
	TC->Font->Color = clBlack;
	TC->Pen->Width = 1;
	TC->Pen->Color = clBlack;

	int alto = TC->TextHeight("0") + 2;
	int ancho = TC->TextWidth("000") + 4;
	int filas = ultFila - iniFila + 1;
	int cols = ultCol - iniCol + 1;
	static int antSizeX = 0;
	static int antSizeY = 0;

	TC->Brush->Color = clClear;
	TC->FillRect(Rect(X, Y, X + antSizeX, Y + antSizeY));
	antSizeX = cols * ancho + 1;
	antSizeY = filas * alto + 1;

	TC->Brush->Style = bsClear;

	for (int fn = 0; fn <= filas; fn++) {
		TC->MoveTo(X, Y + fn*alto );
		TC->LineTo(X + ancho*cols, Y + fn*alto);
	}

	for (int cn = 0; cn <= cols; cn++) {
		TC->MoveTo(X + cn*ancho , Y );
		TC->LineTo(X + cn*ancho , Y + filas*alto);
	}

	SetTextAlign(TC->Handle, TA_CENTER);
	for (int f = 0; f < filas; f++) {
		for (int c = 0; c < cols; c++) {
			TC->TextOut(X + ancho/2 + c*ancho,
						Y + f*alto , elemento(f + iniFila, c + iniCol));
		}
	}
	SetTextAlign(TC->Handle, TA_LEFT);
}

void MatrizDispersa::mostrarATR(int posX, int posY)
{
	TC->Font->Size = 14;
	int h = TC->TextHeight("0");
	static int antSize = 0;
	TC->Brush->Color = clClear;
	TC->FillRect(Rect(posX, posY, posX + antSize, posY + h));

	AnsiString atr1, atr2, atr3, atr4, atr5;
	

	TC->TextOut(posX, posY, atr1);
}
