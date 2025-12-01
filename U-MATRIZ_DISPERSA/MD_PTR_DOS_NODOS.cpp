//---------------------------------------------------------------------------

#pragma hdrstop

#include "MD_PTR_DOS_NODOS.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//--------------------------------------------------------------------------

NodoF* MatrizDispersa::buscarFila(int f)
{
    NodoF* x = ptrFil;
    while (x != nullptr) {
        if (x->fila == f)
            return x;
        x = x->sigF;
    }
    return nullptr;
}

NodoC* MatrizDispersa::buscarCol(NodoF* dirF, int c)
{
    if (dirF == nullptr)
        return nullptr;
    NodoC* x = dirF->ptrCol;
    while (x != nullptr) {
        if (x->col == c)
            return x;
        x = x->sigCol;
    }
    return nullptr;
}

void MatrizDispersa::eliminar(NodoF* dirF, NodoC* dirC)
{
	if (dirC == dirF->ptrCol) {
		dirF->ptrCol = dirC->sigCol;
	} else {
		NodoC* x = dirF->ptrCol;
		while (x->sigCol != dirC)
			x = x->sigCol;
		x->sigCol = dirC->sigCol;
	}
	delete dirC;
	if (dirF->ptrCol == nullptr) {
		NodoF* sig = dirF->sigF;
		NodoF* ant = dirF->antF;
		if (ant == nullptr)
			ptrFil = sig;
		else
			ant->sigF = sig;
		if (sig != nullptr)
			sig->antF = ant;
		delete dirF;
	}
}
//---------------------------------------------------------------------

MatrizDispersa::MatrizDispersa()
{
	ptrFil = nullptr;
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
	NodoF* dirF = buscarFila(f);
	NodoC* dirC = buscarCol(dirF, c);

	if (dirF != nullptr && dirC != nullptr) {
		dirC->dato = valor;
		if (valor == rep)
			eliminar(dirF, dirC);

	} else if (valor != rep) {
		if (dirF == nullptr) {
			dirF = new NodoF;
			dirF->fila = f;
			dirF->ptrCol = nullptr;

			NodoF* act = ptrFil;
			NodoF* ant = nullptr;
			while (act != nullptr && act->fila < f) {
				ant = act;
				act = act->sigF;
			}

			dirF->antF = ant;
			dirF->sigF = act;
			if (ant != nullptr)
				ant->sigF = dirF;
			else
				ptrFil = dirF;

			if (act != nullptr)
				act->antF = dirF;
		}
		dirC = new NodoC;
        dirC->col = c;
        dirC->dato = valor;
        dirC->sigCol = nullptr;

		if (dirF->ptrCol == nullptr)
            dirF->ptrCol = dirC;
        else {
            NodoC* aux = dirF->ptrCol;
            while (aux->sigCol != nullptr)
                aux = aux->sigCol;
            aux->sigCol = dirC;
		}
    }
}

int MatrizDispersa::elemento(int f, int c)
{
	NodoF* dirF = buscarFila(f);
	NodoC* dirC = buscarCol(dirF, c);
	if (dirC != nullptr)
		return dirC->dato;
	else
		return rep;
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
	atr1 = "PTRMATD: " + IntToStr(int(ptrFil));
	atr2 = "DIMF: " + IntToStr(dimF);
	atr3 = "DIMC: " + IntToStr(dimC);
	atr4 = "REPE: " + IntToStr(rep);

	TC->TextOut(posX, posY, atr1);
}
