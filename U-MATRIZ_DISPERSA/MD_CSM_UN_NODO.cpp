//---------------------------------------------------------------------------

#pragma hdrstop

#include "MD_CSM_UN_NODO.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//--------------------------------------------------------------------------

int MatrizDispersa::buscar(int f, int c)
{
	int x = ptrMatD;

	while (x != NULO){
		if ((M->obtener_dato(x,"->fila") == f) && (M->obtener_dato(x,"->col") == c)) {
			return x;
		}
		x = M->obtener_dato(x,"->sig");
	}

	return NULO;
}

void MatrizDispersa::eliminar(int dir)
{
	if (ptrMatD != dir) {
		int x = ptrMatD;
		while (M->obtener_dato(x,"->sig") != dir)
			x = M->obtener_dato(x,"->sig");

		M->poner_dato(x,"->sig", M->obtener_dato(dir,"->sig"));
		M->delete_espacio(dir);
	} else {
		ptrMatD = M->obtener_dato(ptrMatD,"->sig");
		M->delete_espacio(dir);
	}
}

//--------------------------------------------------------------------------
MatrizDispersa::MatrizDispersa()
{
	ptrMatD = NULO;
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
	int dir = buscar(f, c);
	if (dir == NULO) {
		if(valor != rep) {
			int x = M->new_espacio("fila,col,dato,sig");

			if (x != NULO) {
				M->poner_dato(x,"->fila",f);
				M->poner_dato(x,"->col",c);
				M->poner_dato(x,"->dato",valor);
				M->poner_dato(x,"->sig",ptrMatD);
				ptrMatD = x;
			}
			else
				throw Exception("ERROR: NO EXISTE ESPACIO EN MEMORIA");
		}
	} else {
		M->poner_dato(dir,"->dato",valor);
		if (valor == rep) {
		   eliminar(dir);
		}
	}
}

int MatrizDispersa::elemento(int f, int c)
{
	if (((f >= 1) && (f <= dimF)) && ((c >= 1) && (c <= dimC))) {
		int dir = buscar(f, c);
		if (dir != NULO) {
			return M->obtener_dato(dir,"->dato");
		} else {
			return rep;
		}
	}
	else
		throw Exception("ERROR: INDICES FUERA DE RANGO");
}

void MatrizDispersa::definir_valor_repetido(int valor)
{
	if (valor != rep) {
		for (int i = 1; i <= dimF; i++) {
			for (int j = 1; j <= dimC; j++) {
				if (elemento(i, j) == valor) {
					poner(i, j, rep);
				}
			}
		}
		rep = valor;
	}
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
	atr1 = "PTRMATD: " + IntToStr(ptrMatD);
	atr2 = "DIMF: " + IntToStr(dimF);
	atr3 = "DIMC: " + IntToStr(dimC);
	atr4 = "REPE: " + IntToStr(rep);

	TC->TextOut(posX, posY, atr1);
}
