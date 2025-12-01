//---------------------------------------------------------------------------

#ifndef COLA_VECTOR_V2H
#define COLA_VECTOR_V2H
//---------------------------------------------------------------------------
#include <Vcl.h> // Para usar canvas
#include <string>
using namespace std;

extern TCanvas *TC;	// Canvas global al que se le asignara Form->Canvas
extern TColor clClear; // Color para limpiar, se le asignara Form->Color

const int MAX = 1024;
const int NULO = -1;

typedef float ElemQ;

class Cola {
	private:
		ElemQ V[MAX];
		int ini;
		int fin;
		void desplazar(int d);

	public:
		Cola();
		bool vacia();
		void poner(ElemQ e);
		void sacar(ElemQ &e);
		ElemQ primero();

		void mostrar(int x = 200, int y = 20, TColor fondo = clYellow);
		void mostrarATR(int posX = 200, int posY = 60);
};

#endif
