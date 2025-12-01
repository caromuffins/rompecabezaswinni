//---------------------------------------------------------------------------

#ifndef PILA_PUNTEROH
#define PILA_PUNTEROH
//---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <Vcl.Graphics.hpp> // Para usar canvas

extern TCanvas *TC;	// Canvas global al que se le asignara Form->Canvas
extern TColor clClear; // Color para limpiar, se le asignara Form->Color

struct NodoS {
	int elemento;
	NodoS* sig;
};

class Pila {
	private:
		NodoS* tope;

	public:
		Pila();
		void crear();
		bool vacia();
		void meter(int e);
		void sacar(int &e);
		int cima();

		void mostrar(int posX = 300, int posY = 400);
		void mostrarATR(int posX = 400, int posY = 10);
};

#endif
