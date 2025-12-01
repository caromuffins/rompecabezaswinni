//---------------------------------------------------------------------------

#ifndef PILA_LISTAH
#define PILA_LISTAH
//---------------------------------------------------------------------------
//#include "ListaCSMemoria.h"
//#include "ListaPuntero.h"
#include "ListaVector.h"

class Pila {
	private:
		Lista L;

	public:
		Pila() {};
		void crear();
		bool vacia();
		void meter(int e);
		void sacar(int &e);
		int cima();

		void mostrar(int posX = 300, int posY = 400);
		void mostrarATR(int posX = 400, int posY = 10);
};

#endif
