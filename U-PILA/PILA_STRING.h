//---------------------------------------------------------------------------

#ifndef PILA_STRINGH
#define PILA_STRINGH
//---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <Vcl.Graphics.hpp> // Para usar canvas
#include <string>

using namespace std;

extern TCanvas *TC;	// Canvas global al que se le asignara Form->Canvas
extern TColor clClear; // Color para limpiar, se le asignara Form->Color

class Pila {
	private:
		string P;

	public:
		Pila();
		bool vacia();
		void meter(int e);
		void sacar(int &e);
		int cima();

		void mostrar(int posX = 300, int posY = 400);
		void mostrarATR(int posX = 400, int posY = 10);
};

#endif
