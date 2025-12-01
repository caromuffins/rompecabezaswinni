//---------------------------------------------------------------------------

#ifndef COLA_PUNTEROH
#define COLA_PUNTEROH
//---------------------------------------------------------------------------
#include <Vcl.h> // Para usar canvas
#include <string>

using namespace std;

extern TCanvas *TC;	// Canvas global al que se le asignara Form->Canvas
extern TColor clClear; // Color para limpiar, se le asignara Form->Color

struct NodoQ {
	int elemento;
	NodoQ* sig;
};

class Cola {
	private:
		NodoQ* ini;
		NodoQ* fin;

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
