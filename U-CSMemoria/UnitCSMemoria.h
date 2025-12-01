//---------------------------------------------------------------------------

#ifndef UnitCSMemoriaH
#define UnitCSMemoriaH
//---------------------------------------------------------------------------
#include <string>
#include <Vcl.h> // Para usar TCanvas, TColor y throw Exception()

using namespace std;

extern TCanvas *TC;	// Canvas global al que se le asignara Form->Canvas
extern TColor clClear; // Color para limpiar, se le asignara Form->Color

const int MAX = 65535;
const int NULO = -1;

typedef float Dato;

struct NodoM {
	Dato dato;
	string id;
	int link;
};

class CSMemoria {
	private:
		NodoM MEM[MAX];
		int libre;

		int numero_ids(string cadena);
		string obtener_id(string cad, int num_id);
		void eliminar_flecha(string &cadena);

	public:
		CSMemoria();
		int new_espacio(string cadena);
		void delete_espacio(int dir);
		int espacio_disponible();
		int espacio_ocupado();
		void poner_dato(int dir, string cadena_id, Dato valor);
		Dato obtener_dato(int dir, string cadena_id);
		bool dir_libre(int dir);
		void ocultarLinks(int pri, int ult, int posX = 300, int posY = 10);
		void mostrar(int pri, int ult, int posX = 300, int posY = 10);
										// define valores por defecto
										// se aplican si al llamar al metodo
										// no se introduce estos parametros
};
//----------------------------
extern CSMemoria* M;	// Puntero a Memoria Global
						// para que cada proyecto trabaje con una misma memoria
//----------------------------

#endif
