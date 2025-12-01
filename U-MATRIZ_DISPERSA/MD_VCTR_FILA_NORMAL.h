//---------------------------------------------------------------------------

#ifndef MD_VCTR_FILA_NORMALH
#define MD_VCTR_FILA_NORMALH
//---------------------------------------------------------------------------
#include <vcl.h>

extern TCanvas *TC;	// Canvas global al que se le asignara Form->Canvas
extern TColor clClear; // Color para limpiar, se le asignara Form->Color

const int NULO = -1;
const int MAX = 10000;

class MatrizDispersa {    //MATRIZ DISPERSA FILA NO COMPRIMIDA
	private:
		int VF[MAX];
		int VC[MAX];
		int VD[MAX];

		int dimF, dimC;
		int rep;
		int nt;

		int buscar(int f, int c);
		void desplazar(int lug);
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
