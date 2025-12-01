//---------------------------------------------------------------------------

#ifndef MD_CSM_DOS_NODOSH
#define MD_CSM_DOS_NODOSH
//---------------------------------------------------------------------------
#include "UnitCSMemoria.h"

class MatrizDispersa {
	private:
		//CSMemoria M;
		int ptrFil;
		int rep, dimF, dimC;

		int buscarFila(int f);
		int buscarCol(int dirF, int c);
		void eliminar(int dirF, int dirC);

	public:
		MatrizDispersa();
		void dimensionar(int nf,int nc);
		int dimension_fila();
		int dimension_columna();
		void poner(int f, int c, int valor);
		int elemento(int f, int c);
		void definir_valor_repetido(int valor);

		void mostrar(int iniFila, int iniCol, int ultFila, int ultCol, int X=700, int Y=20);

		void mostrarATR(int posX = 200, int posY = 20);
};

#endif
