//---------------------------------------------------------------------------
#pragma hdrstop
#include "ListaCSMemoria.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
Lista::Lista()
{
	longitud = 0;
	ptrElementos = NULO;
}
int Lista::fin()
{
	int dirFin = ptrElementos;
	if (dirFin != NULO) {
		while (M->obtener_dato(dirFin,"->sig") != NULO)
			dirFin = M->obtener_dato(dirFin,"->sig");
	}
	return dirFin;
}
int Lista::primero()
{
	return ptrElementos;
}
int Lista::siguiente(int dir)
{
	if (dir == NULO)
		return NULO;
	return M->obtener_dato(dir,"->sig");
}
int Lista::anterior(int dir)
{
	if (dir == primero() || dir == NULO)
		return NULO;
	int ant = ptrElementos;
	while (M->obtener_dato(ant,"->sig") != dir)
		ant = M->obtener_dato(ant,"->sig");
	return ant;
}
bool Lista::vacia()
{
	return (longitud == 0);
}
ElemL Lista::recupera(int dir)
{
	if (vacia())
		throw Exception("Lista vacia");
	return M->obtener_dato(dir,"->elemento");
}
int Lista::LONGITUD()
{
	return longitud;
}
void Lista::inserta(int dir, ElemL elem)
{
	int x = M->new_espacio("elemento,sig");
	if (x != NULO) {
		M->poner_dato(x,"->elemento",elem);
		M->poner_dato(x,"->sig",dir);
		int ant = anterior(dir);
		if (ant == NULO)
			ptrElementos = x;
		else
			M->poner_dato(ant,"->sig",x);
		longitud++;
	} else
		throw Exception("No existe espacio en Memoria");
}
void Lista::inserta_primero(ElemL elem)
{
	int x = M->new_espacio("elemento,sig");
	if (x != NULO) {
		M->poner_dato(x,"->elemento",elem);
		M->poner_dato(x,"->sig",ptrElementos);
		longitud++;
		ptrElementos = x;
	} else
		throw Exception("No existe espacio en Memoria");
}
void Lista::inserta_ultimo(ElemL elem)
{
	int x = M->new_espacio("elemento,sig");
	if (x != NULO) {
		M->poner_dato(x,"->elemento",elem);
		M->poner_dato(x,"->sig",NULO);
		if (longitud != 0)
			M->poner_dato(fin(),"->sig",x);
		else
			ptrElementos = x;
		longitud++;
	} else
		throw Exception("No existe espacio en Memoria");
}
void Lista::suprime(int dir)
{
	if (longitud == 0)
		throw Exception("Lista Vacia");
	if (dir == ptrElementos) {
		ptrElementos = M->obtener_dato(ptrElementos,"->sig");
		M->delete_espacio(dir);
	} else {
		int ant = anterior(dir);
		M->poner_dato(ant,"->sig",siguiente(dir));
		M->delete_espacio(dir);
	}
	longitud--;
}
void Lista::modifica(int dir, ElemL elem)
{
	if (longitud == 0)
		throw Exception("Lista Vacia");
	M->poner_dato(dir,"->elemento",elem);
}
int Lista::localiza(ElemL elem)
{
	int dir = primero();
	while (dir != NULO) {
		ElemL e = recupera(dir);
		if (e == elem)
			return  dir;
		dir = siguiente(dir);
	}
	return NULO;
}
void Lista::eliminaDato(ElemL elem)
{
	if (!vacia()) {
		int dir = localiza(elem);
		while (dir != NULO) {
			suprime(dir);
			dir = localiza(elem);
		}
	}
	else
		throw Exception("Lista vacia");
}
void Lista::anula()
{
	while (!vacia())
		suprime(fin());
}
void Lista::mostrar(int posX, int posY)
{
	//const int posX = 400, posY = 10;
	TC->Font->Size = 16;
	TC->Font->Color = clRed;
	TC->Font->Style = TFontStyles() << fsBold;
	TC->Pen->Width = 1;
	TC->Pen->Color = clBlack;
	int h = TC->TextHeight("0");
	static int antSize = 0;
	TC->Brush->Color = clClear;
	TC->FillRect(Rect(posX, posY, posX + antSize, posY + h));
	TC->Brush->Style = bsClear;
	AnsiString list = "<";
	int x = ptrElementos;
	while (x != NULO) {
		ElemL e = M->obtener_dato(x,"->elemento");
		list += " " + FloatToStr(e);
		x = M->obtener_dato(x,"->sig");
		if (x != NULO) list += ",";
	}
	list += " >";
	antSize = TC->TextWidth(list) + 1;
	TC->TextOut(posX, posY, list);
    TC->Font->Style = TFontStyles();
}
void Lista::mostrarATR(int posX, int posY)
{
	TC->Font->Size = 14;
	int h = TC->TextHeight("0");
	static int antSize = 0;
	TC->Brush->Color = clClear;
	TC->FillRect(Rect(posX, posY, posX + antSize, posY + h*2 + 5));
	AnsiString atr1, atr2;
	atr1 = "ptrElementos: " + IntToStr(ptrElementos);
	atr2 = "longitud: " + IntToStr(longitud);
	antSize = TC->TextWidth(atr1);
	TC->TextOut(posX, posY, atr1);
	TC->TextOut(posX, posY + 5 + h, atr2);
}
void Lista::ordenar()
{
    if (longitud < 2) return; // Nada que ordenar

    // Usaremos un método burbuja adaptado a punteros
    bool huboCambio;
    do {
        huboCambio = false;
        int ant = NULO;            // anterior
        int act = ptrElementos;    // actual

        while (act != NULO && siguiente(act) != NULO) {
            int sig = siguiente(act);

            ElemL e1 = recupera(act);
            ElemL e2 = recupera(sig);

            if (e1 > e2) {
                // --- Intercambiar nodos act y sig ---
                if (ant == NULO) {
                    // el intercambio es en la cabeza
                    ptrElementos = sig;
                } else {
                    M->poner_dato(ant, "->sig", sig);
                }

                M->poner_dato(act, "->sig", siguiente(sig));
                M->poner_dato(sig, "->sig", act);

                // ahora 'sig' quedó antes que 'act'
                huboCambio = true;

                // avanzar punteros
                ant = sig;
            } else {
                // avanzar normalmente
                ant = act;
                act = sig;
            }
        }
    } while (huboCambio);
}

