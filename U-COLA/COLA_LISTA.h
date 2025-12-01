//---------------------------------------------------------------------------

#ifndef COLA_LISTAH
#define COLA_LISTAH
//---------------------------------------------------------------------------
//#include "ListaCSMemoria.h"
//#include "ListaPuntero.h"
#include "ListaVector.h"

class Cola {
	private:
		Lista L;

	public:
		Cola() {};
		bool vacia();
		void poner(int e);
		void sacar(int &e);
		int primero();

		void mostrar(int x = 500, int y = 10, TColor fondo = clYellow);
		void mostrarATR(int posX = 500, int posY = 50);
};

#endif
