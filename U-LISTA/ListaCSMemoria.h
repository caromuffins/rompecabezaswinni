//---------------------------------------------------------------------------

#ifndef ListaCSMemoriaH
#define ListaCSMemoriaH
//---------------------------------------------------------------------------

#include "UnitCSMemoria.h"

typedef int Direccion;
typedef float ElemL;

class Lista {
	private:
		//CSMemoria M;
		int ptrElementos;
		int longitud;

	public:
		Lista();
		int fin();
		int primero();
		int siguiente(int dir);
		int anterior(int dir);
		bool vacia();
		ElemL recupera(int dir);
		int LONGITUD();
		void inserta(int dir, ElemL elem);
		void inserta_primero(ElemL elem);
		void inserta_ultimo(ElemL elem);
		void suprime(int dir);
		void modifica(int dir, ElemL elem);

		int localiza(ElemL elem);
		void eliminaDato(ElemL elem);
		void anula();

		void mostrar(int posX = 700, int posY = 10);
		void mostrarATR(int posX = 700, int posY = 35);
        void ordenar();
};


#endif
