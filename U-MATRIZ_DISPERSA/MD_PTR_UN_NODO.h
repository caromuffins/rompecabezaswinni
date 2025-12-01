//---------------------------------------------------------------------------

#ifndef MD_PTR_UN_NODOH
#define MD_PTR_UN_NODOH
//---------------------------------------------------------------------------
#include <vcl.h>

extern TCanvas *TC;	// Canvas global al que se le asignara Form->Canvas
extern TColor clClear; // Color para limpiar, se le asignara Form->Color

struct NodoMatD {
	int fila;
	int col;
	int dato;
	NodoMatD* sig;
};

class MatrizDispersa {    //MATRIZ DISPERSA PUNTERO FILA COMPRIMIDA
	private:
		NodoMatD *ptrMatD;
		int rep, dimF, dimC;

		NodoMatD* buscar(int f, int c);
		void eliminar(NodoMatD* dir);
	public:
		MatrizDispersa();
		void dimensionar(int nf, int nc);
		int dimension_fila();
		int dimension_columna();
		void poner(int f, int c, int valor);
		int elemento(int f, int c);
		void definir_valor_repetido(int valor);

		void mostrar(int iniFila, int iniCol, int ultFila, int ultCol, int X=600, int Y=20);

		void mostrarATR(int posX = 400, int posY = 20);
};

#endif
