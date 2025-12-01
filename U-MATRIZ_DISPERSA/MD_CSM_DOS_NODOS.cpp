//---------------------------------------------------------------------------

#pragma hdrstop

#include "MD_CSM_DOS_NODOS.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//--------------------------------------------------------------------------

int MatrizDispersa::buscarFila(int f)
{
	int x = ptrFil;

	while (x != NULO){
		if (M->obtener_dato(x,"->fila") == f) {
			return x;
		}
		x = M->obtener_dato(x,"->sigF");
	}

	return NULO;
}

int MatrizDispersa::buscarCol(int dirF, int c)
{
	if (dirF == NULO) return NULO;

	int x = M->obtener_dato(dirF,"->ptrCol");

	while (x != NULO){
		if (M->obtener_dato(x,"->col") == c) {
			return x;
		}
		x = M->obtener_dato(x,"->sigCol");
	}

	return NULO;
}

void MatrizDispersa::eliminar(int dirF, int dirC)
{
	int x = M->obtener_dato(dirF,"->ptrCol");
	if (dirC == x) {
		M->poner_dato(dirF,"->ptrCol",M->obtener_dato(dirC,"->sigCol"));
	} else {
		while (M->obtener_dato(x,"->sigCol") != dirC)
			x = M->obtener_dato(x,"->sigCol");
		M->poner_dato(x,"->sigCol",M->obtener_dato(dirC,"->sigCol"));
	}
	M->delete_espacio(dirC);
	if (M->obtener_dato(dirF,"->ptrCol") == NULO) {
		int sig = M->obtener_dato(dirF,"->sigF");
		int ant = M->obtener_dato(dirF,"->antF");
		if (ant == NULO)
			ptrFil = sig;
		else
			M->poner_dato(ant,"->sigF",sig);
		if (sig != NULO)
			M->poner_dato(sig,"->antF",ant);
		M->delete_espacio(dirF);
	}
}
//--------------------------------------------------------------------------
MatrizDispersa::MatrizDispersa()
{
	ptrFil = NULO;
	dimF = 0;
	dimC = 0;
	rep = 0;
}

void MatrizDispersa::dimensionar(int nf,int nc)
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
	int dirF = buscarFila(f);
	int dirC = buscarCol(dirF, c);

	if (dirF != NULO && dirC != NULO) {
		M->poner_dato(dirC,"->dato",valor);
		if (valor == rep)
			eliminar(dirF, dirC);

	} else if (valor != rep) {
		if (dirF == NULO) {
			dirF = M->new_espacio("fila,sigF,antF,ptrCol");
			M->poner_dato(dirF,"->fila",f);
			M->poner_dato(dirF,"->ptrCol",NULO);

			int act = ptrFil;
			int ant = NULO;
			while (act != NULO && M->obtener_dato(act,"->fila") < f) {
				ant = act;
				act = M->obtener_dato(act,"->sigF");
			}

			M->poner_dato(dirF,"->antF",ant);
			M->poner_dato(dirF,"->sigF",act);
			if (ant != NULO)
				M->poner_dato(ant,"->sigF",dirF);
			else
				ptrFil = dirF;

			if (act != NULO)
				M->poner_dato(act,"->antF",dirF);
		}
		dirC = M->new_espacio("col,dato,sigCol");
		M->poner_dato(dirC,"->col",c);
		M->poner_dato(dirC,"->dato",valor);
		M->poner_dato(dirC,"->sigCol",NULO);

		if (M->obtener_dato(dirF,"->ptrCol") == NULO)
			M->poner_dato(dirF,"->ptrCol",dirC);
		else {
			int aux = M->obtener_dato(dirF,"->ptrCol");
			while (M->obtener_dato(aux,"->sigCol") != NULO)
				aux = M->obtener_dato(aux,"->sigCol");
			M->poner_dato(aux,"->sigCol",dirC);
		}
	}
}

int MatrizDispersa::elemento(int f, int c)
{
	if (((f >= 1) && (f <= dimF)) && ((c >= 1) && (c <= dimC))) {
		int dirF = buscarFila(f);
		int dirC = buscarCol(dirF, c);
		if (dirC != NULO)
			return M->obtener_dato(dirC,"->dato");
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

	int w = 0;

	AnsiString atr1, atr2, atr3, atr4, atr5, atr6;
	atr1 = "PTRMATF: " + IntToStr(ptrFil);
	atr2 = "DIMF: " + IntToStr(dimF);
	atr3 = "DIMC: " + IntToStr(dimC);
	atr4 = "REPE: " + IntToStr(rep);

	int x = ptrFil;
	int i = 2;
	while (x != NULO) {
		TC->TextOut(posX, posY + h*(i-1), "NodoFila: " + IntToStr(x));
		atr5 = "|";
		atr5 += FloatToStr(M->obtener_dato(x,"->fila")) + " | ";
		atr5 += FloatToStr(M->obtener_dato(x,"->sigF")) + " | ";
		atr5 += FloatToStr(M->obtener_dato(x,"->antF")) + " | ";
		atr5 += FloatToStr(M->obtener_dato(x,"->ptrCol")) + "|";
		TC->TextOut(posX, posY + h*i, atr5);
		w = TC->TextWidth(atr5);
		int y = M->obtener_dato(x,"->ptrCol");
		int j = 1;
		while (y != NULO) {
			atr6 = "-> |";
			atr6 += FloatToStr(M->obtener_dato(y,"->col")) + " | ";
			atr6 += FloatToStr(M->obtener_dato(y,"->dato")) + " | ";
			atr6 += FloatToStr(M->obtener_dato(y,"->sigCol")) + " | ";
			TC->TextOut(posX + 10 + w*j, posY + h*i, atr6);
			w = TC->TextWidth(atr6);
			j++;
			y = M->obtener_dato(y,"->sigCol");
		}
		i += 2;
		w = 0;
		x = M->obtener_dato(x,"->sigF");
	}
	TC->TextOut(posX, posY + h*i++, atr1);
	TC->TextOut(posX, posY + h*i++, atr2);
	TC->TextOut(posX, posY + h*i++, atr3);
	TC->TextOut(posX, posY + h*i, atr4);
}
