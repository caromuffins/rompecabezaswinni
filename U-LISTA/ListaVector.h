//---------------------------------------------------------------------------

#ifndef ListaVectorH
#define ListaVectorH
//---------------------------------------------------------------------------
#include <Vcl.h>

extern TCanvas *TC;
extern TColor clClear;

using namespace std;

const int MAXV = 1024;
const int NULOV = -1;

typedef int Direccion;
typedef float ElemL;

class Lista {
	private:
		float elementos[MAXV];
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

		void mostrar(int posX = 400, int posY = 10);
		void mostrarATR(int posX = 400, int posY = 35);
};

#endif
