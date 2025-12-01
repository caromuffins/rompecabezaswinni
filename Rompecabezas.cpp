//---------------------------------------------------------------------------

#pragma hdrstop

#include "Rompecabezas.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

Rompecabezas::Rompecabezas()
{
	IniciarJuego();
}
//---------------------------------------------------------------------------
void Rompecabezas::IniciarJuego()
{
	int n = 3;
	int a = 0;
	MD.dimensionar(n, n);

	// Paleta pastel (static const para evitar inicialización repetida)
	static const TColor coloresPastel[] = {
		TColor(0xFFE4E1), // Rosa pastel
		TColor(0xE6E6FA), // Lavanda
		TColor(0xF0E68C), // Amarillo pastel
		TColor(0xB0E0E6), // Azul pastel
		TColor(0xDDA0DD), // Ciruela pastel
		TColor(0xF5DEB3), // Trigo pastel
		TColor(0xFFDAB9), // Durazno pastel
		TColor(0xE0BBE4)  // Lila pastel
	};

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			MD.poner(i, j, a + 1);

			if (a != ((n*n)-1)) {
				p[a].id = a + 1;
				p[a].fila = i;
				p[a].col = j;
				p[a].color = coloresPastel[a % 8];  // Ciclar colores
			} else {
				z.id = 0;
				z.fila = i;
				z.col = j;
				z.color = TColor(0xF5F5F5);  // Blanco humo (muy suave)
			}
			a++;
		}
	}
	MD.poner(n, n, 0);

	cantPiezas = n*n - 1;
}

bool Rompecabezas::Solucionado()
{
	int a = 1;
	for (int i = 1; i <= MD.dimension_fila(); i++) {
		for (int j = 1; j <= MD.dimension_columna(); j++) {
			if (MD.elemento(i, j) != a)
				return false;
			a++;
			if (a == 9) {
                a = 0;
			}
		}
	}
	return true;
}

void Rompecabezas::MoverZ(int mov, bool g)
{
	switch (mov) {
	case 0: {
		if (deslizarIzquierda() && g) P.meter(2);
		break;
	}
	case 1: {
		if (deslizarArriba() && g) P.meter(3);
		break;
	}
	case 2: {
		if (deslizarDerecha() && g) P.meter(0);
		break;
	}
	case 3: {
		if (deslizarAbajo() && g) P.meter(1);
		break;
	}
	default:
		break;
	}
}

void Rompecabezas::Retroceder()
{
	if (!P.vacia()) {
		int k;
		P.sacar(k);
		MoverZ(k, false);
	}
}

bool Rompecabezas::deslizarIzquierda()
{
	if (z.col == MD.dimension_columna())
		return false;

	int i;
	for (i = 0; i < cantPiezas; i++) {
		if ((p[i].col - 1 == z.col) && (p[i].fila == z.fila))
			break;
	}

	int c;
	c = p[i].col;
	p[i].col = z.col;
	z.col = c;

	MD.poner(p[i].fila, p[i].col, p[i].id);
	MD.poner(z.fila, z.col, z.id);
	return true;
}

bool Rompecabezas::deslizarArriba()
{
	if (z.fila == MD.dimension_fila())
		return false;

	int i;
	for (i = 0; i < cantPiezas; i++) {
		if ((p[i].fila - 1 == z.fila) && (p[i].col == z.col))
			break;
	}

	int f;
	f = p[i].fila;
	p[i].fila = z.fila;
	z.fila = f;

	MD.poner(p[i].fila, p[i].col, p[i].id);
	MD.poner(z.fila, z.col, z.id);
	return true;
}

bool Rompecabezas::deslizarDerecha()
{
	if (z.col == 1)
		return false;

	int i;
	for (i = 0; i < cantPiezas; i++) {
		if ((p[i].col + 1 == z.col) && (p[i].fila == z.fila))
			break;
	}

	int c;
	c = p[i].col;
	p[i].col = z.col;
	z.col = c;

	MD.poner(p[i].fila, p[i].col, p[i].id);
	MD.poner(z.fila, z.col, z.id);
	return true;
}

bool Rompecabezas::deslizarAbajo()
{
	if (z.fila == 1)
		return false;

	int i;
	for (i = 0; i < cantPiezas; i++) {
		if ((p[i].fila + 1 == z.fila) && (p[i].col == z.col))
			break;
	}

	int f;
	f = p[i].fila;
	p[i].fila = z.fila;
	z.fila = f;

	MD.poner(p[i].fila, p[i].col, p[i].id);
	MD.poner(z.fila, z.col, z.id);
    return true;
}

void Rompecabezas::Dibujar(int posX, int posY)
{
	TC->Font->Size = 16;
	int d = TC->TextHeight("0") * 2;
	SetTextAlign(TC->Handle, TA_CENTER);
	for (int i = 0; i < MD.dimension_fila(); i++) {
		int x = posX + d;
		for (int j = 0; j < MD.dimension_columna(); j++) {
			int e = MD.elemento(i+1, j+1);
			if (e == 0)
				z.dibujar(x, posY);
			else
				p[e-1].dibujar(x, posY);
            x += d + 5;
		}
		posY += d + 5;
	}
    SetTextAlign(TC->Handle, TA_LEFT);
}