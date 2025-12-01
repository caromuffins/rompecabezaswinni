//---------------------------------------------------------------------------

#ifndef PILA_VECTORH
#define PILA_VECTORH
//---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <Vcl.Graphics.hpp> // Para usar canvas

extern TCanvas *TC;	// Canvas global al que se le asignara Form->Canvas
extern TColor clClear; // Color para limpiar, se le asignara Form->Color

const int MAXP = 500;
const int NULOP = -1;

class Pila {
	private:
		int tope;
		int elementos[MAXP];

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
