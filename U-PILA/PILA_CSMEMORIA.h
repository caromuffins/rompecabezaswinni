//---------------------------------------------------------------------------

#ifndef PILA_CSMEMORIAH
#define PILA_CSMEMORIAH
//---------------------------------------------------------------------------
#include "UnitCSMemoria.h"

class Pila {
	private:
		//CSMemoria M;
		int tope;

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
