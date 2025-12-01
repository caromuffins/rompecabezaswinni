//---------------------------------------------------------------------------

#pragma hdrstop

#include "MD_PTR_UN_NODO.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//--------------------------------------------------------------------------

NodoMatD* MatrizDispersa::buscar(int f, int c)
{
	NodoMatD* x = ptrMatD;

	while (x != nullptr){
		if ((x->fila == f) && (x->col == c)) {
			return x;
		}
		x = x->sig;
	}

	return nullptr;
}

void MatrizDispersa::eliminar(NodoMatD* dir)
{
	if (ptrMatD != dir) {
		NodoMatD* x = ptrMatD;
		while (x->sig != dir)
			x = x->sig;

		x->sig = dir->sig;
		delete dir;
	} else {
		ptrMatD = ptrMatD->sig;
		delete dir;
	}
}
//---------------------------------------------------------------------

MatrizDispersa::MatrizDispersa()
{
	ptrMatD = nullptr;
	rep = 0;
	dimF = 0;
	dimC = 0;
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
	NodoMatD* x = buscar(f, c);
	if (x == nullptr) {
		if (valor != rep) {
			x = new NodoMatD;
			if (x != nullptr) {
				x->fila = f;
				x->col = c;
				x->dato = valor;
				x->sig = ptrMatD;
				ptrMatD = x;
			} else
				throw Exception("ERROR: NO EXISTE ESPACIO EN MEMORIA");
		}
	} else {
		x->dato = valor;
		if (valor == rep) {
		   eliminar(x);
		}
	}
}

int MatrizDispersa::elemento(int f, int c)
{
	if (((f >= 1) && (f <= dimF)) && ((c >= 1) && (c <= dimC))) {
		NodoMatD* dir = buscar(f, c);
		if (dir != nullptr)
			return dir->dato;
		else
			return rep;
	}
	else
		throw Exception("ERROR: INDICES FUERA DE RANGO");
}

void MatrizDispersa::definir_valor_repetido(int valor)
{
	for (int i = 1; i <= dimF; i++) {
		for (int j = 1; j <= dimC; j++) {
			if (elemento(i, j) == valor) {
				poner(i, j, rep);
			}
		}
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
	atr1 = "PTRMATD: " + IntToStr(int(ptrMatD));
	atr2 = "DIMF: " + IntToStr(dimF);
	atr3 = "DIMC: " + IntToStr(dimC);
	atr4 = "REPE: " + IntToStr(rep);

	TC->TextOut(posX, posY, atr1);
}
