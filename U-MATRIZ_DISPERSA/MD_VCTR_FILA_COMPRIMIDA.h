//---------------------------------------------------------------------------

#ifndef MD_VCTR_FILA_COMPRIMIDAH
#define MD_VCTR_FILA_COMPRIMIDAH
//---------------------------------------------------------------------------
#include <vcl.h>

extern TCanvas *TC;	// Canvas global al que se le asignara Form->Canvas
extern TColor clClear; // Color para limpiar, se le asignara Form->Color

const int MAXMD = 100000;
const int NULOMD = -1;

class MatrizDispersa {    //MATRIZ DISPERSA VECTOR FILA COMPRIMIDA
	private:
		int VF[MAXMD];
		int VC[MAXMD];
		int VD[MAXMD];

		int dimF, dimC;
		int rep;
		int nt;

		int existe_elemento(int f, int c);
		int donde_insertar(int f, int c);

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
