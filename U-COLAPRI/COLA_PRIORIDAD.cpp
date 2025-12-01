//---------------------------------------------------------------------------

#pragma hdrstop

#include "COLA_PRIORIDAD.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

ColaPri::ColaPri()
{
	for (int i = 0; i < PMAX; i++) {
		VF[i] = 1;
	}
	colaAct = 0;
	cant = 0;
}

bool ColaPri::vacia()
{
	bool vacia = true;
	int i = 0;
	while (i < PMAX && vacia) {
		vacia = VC[i].vacia();
		i++;
	}
	return vacia;
}

int ColaPri::primero()
{
	if (!vacia())
		return VC[colaAct].primero();
	else
		throw Exception("ERROR: COLAS VACIAS");
}

void ColaPri::poner(int e, int prioridad)
{
	VC[prioridad].poner(e);
}

void ColaPri::Asignar_Frecuencia_Prioridad(int frec, int prioridad)
{
	VF[prioridad] = frec;
}

void ColaPri::sacar(int &e)
{
	int intentos = 0;
	while (intentos < PMAX) {
		if (!VC[colaAct].vacia() && VF[colaAct] != 0) {
			VC[colaAct].sacar(e);
			cant++;
			if (cant == VF[colaAct]) {
				colaAct = (colaAct + 1) % PMAX;
				cant = 0;
			}
			intentos = PMAX;
		} else {
			colaAct = (colaAct + 1) % PMAX;
			cant = 0;
			intentos++;
			if (intentos == PMAX)
				throw Exception("Cola de prioridad VACIA");
		}
	}
}

void ColaPri::mostrar(int posX, int posY)
{
	TColor pal[] = { clSkyBlue, clLime, clSilver };
    TC->Font->Size = 16;
	int w = TC->TextWidth("00");
	int h = TC->TextHeight("0");
	for (int i = 0; i < PMAX; i++) {
		SetTextAlign(TC->Handle, TA_CENTER);
		TC->Brush->Color = pal[i];
		TC->Rectangle(posX, posY + 30*i, posX + w, posY + 30*i + h);
		TC->Brush->Style = bsClear;
		TC->TextOut(posX + w*0.5, posY + 30*i, VF[i]);
		SetTextAlign(TC->Handle, TA_LEFT);
		VC[i].mostrar(posX + w + 10, posY + 30*i, pal[i]);
	}
}