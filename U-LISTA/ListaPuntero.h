//---------------------------------------------------------------------------

#ifndef ListaPunteroH
#define ListaPunteroH
//---------------------------------------------------------------------------
#include <Vcl.h>

extern TCanvas *TC;
extern TColor clClear;

using namespace std;

// si tiene una version que no tiene nullptr, descomente la siguiente linea
//const int nullptr = NULL;

typedef float ElemL;

struct Nodo {
	ElemL elemento;
	Nodo* sig;
};

typedef Nodo* Direccion;

class Lista {
	private:
		Nodo* ptrElementos;
		int longitud;

	public:
		Lista();
		Nodo* fin();
		Nodo* primero();
		Nodo* siguiente(Nodo* dir);
		Nodo* anterior(Nodo* dir);
		bool vacia();
		ElemL recupera(Nodo* dir);
		int LONGITUD();
		void inserta(Nodo* dir, ElemL elem);
		void inserta_primero(ElemL elem);
		void inserta_ultimo(ElemL elem);
		void suprime(Nodo* dir);
		void modifica(Nodo* dir, ElemL elem);

		Nodo* localiza(ElemL elem);
		void eliminaDato(ElemL elem);
		void anula();

		void mostrar(int posX = 400, int posY = 10);
		void mostrarATR(int posX = 400, int posY = 35);
};

#endif
