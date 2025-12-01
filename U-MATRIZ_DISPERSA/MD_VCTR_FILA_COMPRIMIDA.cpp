//---------------------------------------------------------------------------

#pragma hdrstop

#include "MD_VCTR_FILA_COMPRIMIDA.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//--------------------------------------------------------------------------

int MatrizDispersa::existe_elemento(int f, int c)
{
    int iniCol = VF[f-1] - 1;
    int finCol = VF[f] - 2;
    while (iniCol <= finCol) {
        if (VC[iniCol] == c)
            return iniCol;
        iniCol++;
    }
    return NULOMD;
}

int MatrizDispersa::donde_insertar(int f, int c)
{
    int iniCol = VF[f-1] - 1;
    int finCol = VF[f] - 2;
    while (iniCol <= finCol && c > VC[iniCol])
        iniCol++;
    return iniCol;
}
//---------------------------------------------------------------------

MatrizDispersa::MatrizDispersa()
{
    rep = 0;
    nt = 0;
    dimF = 0;
    dimC = 0;
    VF[0] = 1;
}

void MatrizDispersa::dimensionar(int nf, int nc)
{
    for (int i = dimF; i < nf; i++) {
        VF[i + 1] = VF[i];
    }
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
    int lug = existe_elemento(f, c);
    if (lug == NULOMD) {
        if (valor == rep) return;
        lug = donde_insertar(f, c);
        for (int i = nt; i > lug; i--) {
            VD[i] = VD[i - 1];
            VC[i] = VC[i - 1];
        }
        VD[lug] = valor;
        VC[lug] = c;
        for (; f <= dimF; f++) {
            VF[f]++;
        }
        nt++;
    } else {
        if (valor != rep)
            VD[lug] = valor;
        else {
            for (int i = lug; i < nt; i++) {
                VD[i] = VD[i + 1];
                VC[i] = VC[i + 1];
            }
            for (; f <= dimF; f++) {
                VF[f]--;
            }
            nt--;
        }
    }
}

int MatrizDispersa::elemento(int f, int c) {
    int pos = existe_elemento(f, c);
    if (pos != NULOMD)
        return VD[pos];
    else
        return rep;
}

void MatrizDispersa::definir_valor_repetido(int valor)
{
    for (int i = 1; i <= dimF; i++) {
        for (int j = 1; j <= dimC; j++) {
            int lug = existe_elemento(i, j);
            if (VD[lug] == valor) {
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
	AnsiString ntStr = "NT: " + IntToStr(nt);
	AnsiString DFil = "DF: " + IntToStr(dimF);
	AnsiString DCol = "DC: " + IntToStr(dimC);
	String va = "Rep: " + IntToStr(rep);

	// Cadena de VD (Vector de Datos)
	AnsiString vdStr = "VD = [";
	for (int i = 0; i < nt; i++) {
		vdStr += IntToStr(VD[i]);
		if (i < nt - 1) vdStr += ",  ";
	}
	vdStr += "]";

	// Cadena de VC (Vector de Columnas)
	AnsiString vcStr = "VC = [";
	for (int i = 0; i < nt; i++) {
		vcStr += IntToStr(VC[i]);
		if (i < nt - 1) vcStr += ",  ";
	}
	vcStr += "]";

	// Cadena de VF (Vector de Filas)
	AnsiString vfStr = "VF = [";
	for (int i = 0; i <= dimF; i++) {
		vfStr += IntToStr(VF[i]);
		if (i < dimF) vfStr += ",  ";
	}
	vfStr += "]";

	// Imprimir Atributos
	//TC->TextOut(posX, posY - 30, ntStr); // Numero de Terminos
	TC->TextOut(posX, posY, vdStr); // Vector Datos
	TC->TextOut(posX, posY + 30, vcStr); // Vector Columnas
	TC->TextOut(posX, posY + 60, vfStr); // Vector Filas
	TC->TextOut(posX, posY + 90, va); // Valor por Defecto
	//TC->TextOut(posX, posY + 120, DFil); // Dimension Filas
	//TC->TextOut(posX, posY + 150, DCol); // Dimension Columnas
}
