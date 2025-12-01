//---------------------------------------------------------------------------

#ifndef RompecabezasH
#define RompecabezasH
//---------------------------------------------------------------------------
// -- MATRICES --
//#include "MD_CSM_UN_NODO.h"
//#include "MD_CSM_DOS_NODOS.h"
//#include "MD_PTR_UN_NODO.h"
//#include "MD_PTR_DOS_NODOS.h"
//#include "MD_VCTR_FILA_NORMAL.h"
#include "MD_VCTR_FILA_COMPRIMIDA.h"

// -- PILAS --
//#include "PILA_CSMEMORIA.h"
//#include "PILA_LISTA.h"
#include "PILA_PUNTERO.h"
//#include "PILA_VECTOR.h"

// -- COLAS (Dentro del archivo) --
#include "COLA_PRIORIDAD.h"

const int MAX_PIEZAS = 100; // hasta matriz de 10x10

struct Pieza {
	int id;
	int fila, col;
	TColor color;

	void dibujar(int x, int y) {
		int alto = TC->TextHeight("0") * 2;
		int ancho = alto;

		int w = ancho * 0.5;
		int h = alto*0.25;

		TC->Brush->Color = clYellow;
		TC->Rectangle(x, y, x + ancho, y + alto);

		TC->Brush->Style = bsClear;
		TC->TextOut(x + w, y + h, id);
	}
};

class Rompecabezas {
	private:
        MatrizDispersa MD;
		Pila P;
		Pieza p[MAX_PIEZAS];
		Pieza z;
		int cantPiezas;

	public:
		Rompecabezas();
		void IniciarJuego();
		bool Solucionado();
		void MoverZ(int mov, bool g=true);
		void Retroceder();
        int AnteriorMov();
		bool deslizarIzquierda();
		bool deslizarArriba();
		bool deslizarDerecha();
		bool deslizarAbajo();
		void Dibujar(int posX, int posY);
};

#endif
