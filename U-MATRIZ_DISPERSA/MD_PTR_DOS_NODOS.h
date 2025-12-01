//---------------------------------------------------------------------------

#ifndef MD_PTR_DOS_NODOSH
#define MD_PTR_DOS_NODOSH
//---------------------------------------------------------------------------
#include <vcl.h>

extern TCanvas *TC;	// Canvas global al que se le asignara Form->Canvas
extern TColor clClear; // Color para limpiar, se le asignara Form->Color

struct NodoC {
    int col;
    NodoC *sigCol;
    int dato;
};

struct NodoF {
    int fila;
    NodoF *antF;
    NodoF *sigF;
    NodoC *ptrCol;
};

class MatrizDispersa {    //MATRIZ DISPERSA PUNTERO FILA COMPRIMIDA
    private:
        NodoF *ptrFil;
        int rep, dimF, dimC;

        NodoF* buscarFila(int f);
        NodoC* buscarCol(NodoF* dirF, int c);
        void eliminar(NodoF* dirF, NodoC* dirC);
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
