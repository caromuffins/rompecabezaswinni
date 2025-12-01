//---------------------------------------------------------------------------

#ifndef MD_CSM_UN_NODOH
#define MD_CSM_UN_NODOH
//---------------------------------------------------------------------------
#include "UnitCSMemoria.h"

class MatrizDispersa {
	private:
		//CSMemoria M;
		int ptrMatD;
		int rep;
		int dimF;
		int dimC;

		int buscar(int f, int c);
		void eliminar(int dir);
	public:
		MatrizDispersa();
		void dimensionar(int nf,int nc);
		int dimension_fila();
		int dimension_columna();
		void poner(int f, int c, int valor);
		int elemento(int f, int c);
		void definir_valor_repetido(int valor);

		void mostrar(int iniFila, int iniCol, int ultFila, int ultCol, int X=600, int Y=20);

		void mostrarATR(int posX = 400, int posY = 20);
};

#endif
