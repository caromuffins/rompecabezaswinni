//---------------------------------------------------------------------------

#ifndef COLA_VECTOR_V3H
#define COLA_VECTOR_V3H
//---------------------------------------------------------------------------
#include <Vcl.h> // Para usar canvas
#include <string>
using namespace std;

extern TCanvas *TC;	// Canvas global al que se le asignara Form->Canvas
extern TColor clClear; // Color para limpiar, se le asignara Form->Color

const int MAXC = 1024;
const int NULOC = -1;

class Cola {
	private:
		int V[MAXC];
		int ini;
		int fin;
		int siguiente(int dir);

	public:
		Cola();
		bool vacia();
		void poner(int e);
		void sacar(int &e);
		int primero();

		void mostrar(int x = 200, int y = 20, TColor fondo = clYellow);
		void mostrarATR(int posX = 200, int posY = 60);
};

#endif
