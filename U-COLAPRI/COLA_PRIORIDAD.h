//---------------------------------------------------------------------------

#ifndef COLA_PRIORIDADH
#define COLA_PRIORIDADH
//---------------------------------------------------------------------------
#include "COLA_CSMEMORIA.h"
//#include "COLA_VECTOR_V3.h"
//#include "COLA_PUNTERO.h"
//#include "COLA_LISTA.h"

const int PMAX = 2;

class ColaPri {
	private:
		Cola VC[PMAX];
		int VF[PMAX];
		int colaAct;
		int cant;

	public:
		ColaPri();
		bool vacia();
		int primero();
		void poner(int e, int prioridad);
		void Asignar_Frecuencia_Prioridad(int frec, int prioridad);
		void sacar(int &e);

		void mostrar(int posX=300, int posY=10);
};

#endif
