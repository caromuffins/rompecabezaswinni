//---------------------------------------------------------------------------

#ifndef COLA_CSMEMORIAH
#define COLA_CSMEMORIAH
//---------------------------------------------------------------------------
#include "UnitCSMemoria.h"

class Cola {
	private:
		//CSMemoria M;
		int ini;
		int fin;

	public:
		Cola();
		bool vacia();
		void poner(int e);
		void sacar(int &e);
		int primero();

		void mostrar(int x = 500, int y = 20, TColor fondo = clYellow);
		void mostrarATR(int posX = 500, int posY = 60);
};

#endif
