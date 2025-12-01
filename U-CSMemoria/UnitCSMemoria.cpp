//---------------------------------------------------------------------------
#pragma hdrstop
#include "UnitCSMemoria.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------- METODOS AUXILIARES -------------------------------
int CSMemoria::numero_ids(string cadena)
{
	int ids = 1, pos = cadena.find(',');
	while (pos >= 0){
		ids++;
		cadena.erase(0,pos+1);
		pos = cadena.find(',');
	}
	return ids;
}
string CSMemoria::obtener_id(string cad, int num_id)
{
	int pos = cad.find(',');
	if (pos < 0) {
		return cad;
	}
	int n = 1;
	while (n != num_id) {
		cad = cad.substr(pos+1);
		n++;
		pos = cad.find(',');
	}
	return cad.substr(0,pos);
}
void CSMemoria::eliminar_flecha(string &cadena)
{
	// Verificar si la cadena comienza con "->"
	if (cadena.substr(0, 2) == "->") {
		cadena.erase(0, 2);  // Elimina los primeros dos caracteres "->"
		if (cadena.empty())
			throw Exception("ID no especificado después de '->'");
	}
	else
		throw Exception("Símbolo '->' no encontrado al inicio de la cadena");
}
//--------------------------------------------------------------------------
//----------------------- METODOS PRINCIPALES ------------------------------
//--------------------------------------------------------------------------
CSMemoria::CSMemoria()
{
	for (int i = 0; i < MAX; i++) {
		MEM[i].link = i + 1;
		MEM[i].dato = 0;
		MEM[i].id = "";
	}
	MEM[MAX - 1].link = NULO;
	libre = 0;
}
int CSMemoria::new_espacio(string cadena)
{
	int cant = numero_ids(cadena);
	if (cant > espacio_disponible() || cant == 0)
		return NULO;
	int dir_ocupa = libre;
	int d = libre;
	for (int i = 1; i < cant; i++) {
		MEM[d].id = obtener_id(cadena, i);
		d = MEM[d].link;
	}
	libre = MEM[d].link;
	MEM[d].link = NULO;
	MEM[d].id = obtener_id(cadena, cant);
	return dir_ocupa;
}
void CSMemoria::delete_espacio(int dir)
{
	if (!dir_libre(dir)) {
		int x = dir;
		while (MEM[x].link != NULO)
			x = MEM [x].link;
		MEM[x].link = libre;
		libre = dir;
	}
	else
		throw Exception("Esa direccion ya está libre");
}
int CSMemoria::espacio_disponible()
{
	int x = libre;
	int c = 0;    // CONTADOR
	while (x != NULO){
		c++;
		x = MEM[x].link;
	}
	return c;
}
int CSMemoria::espacio_ocupado()
{
	int c = MAX;
	c = c - espacio_disponible();
	return c;
}
void CSMemoria::poner_dato(int dir, string cadena_id, Dato valor)
{
	int z = dir;
	eliminar_flecha(cadena_id);
	while (z != NULO) {
		if (MEM[z].id == cadena_id)
			   MEM[z].dato = valor;
		z = MEM[z].link;
	}
}
Dato CSMemoria::obtener_dato(int dir, string cadena_id)
{
	int z = dir;
	eliminar_flecha(cadena_id);
	while (z != NULO){
		if (MEM[z].id == cadena_id)
			return MEM[z].dato;
		z = MEM[z].link;
	}
	throw Exception("Direccion o ID incorrecto.");
}
bool CSMemoria::dir_libre(int dir)
{
	int x = libre;
	bool c = false;    // BANDERA
	while ((x != NULO) && (c == false)){
		if (x == dir) c = true;
		x = MEM[x].link;
	}
	return c;
}

void CSMemoria::ocultarLinks(int pri, int ult, int posX, int posY)
{
	if (ult >= MAX)
		ult = MAX - 1;
	int cn = ult - pri + 1;

	// Ajustes del lienzo
	TC->Font->Size = 10;
	TC->Font->Color = clBlack;
	TC->Pen->Width = 1;

	// ancho y alto de celdas
	int w = TC->TextWidth("1234567890");
	int h = TC->TextHeight("0");

	for (int i = 0; i < cn; i++) {
		int idx = pri + i;
		if (!dir_libre(idx)) {
			// OCULTAR LINK: borrar la columna de LINK
			TC->Brush->Color = clClear;
			TC->FillRect(Rect(posX + w * 3, posY + h * (i + 1),
							  posX + w * 4 + 1,     posY + h * (i + 2)));
		}
	}
}

void CSMemoria::mostrar(int pri, int ult, int posX, int posY)
{
	// Cantidad de celdas a dibujar
	if (ult >= MAX)
		ult = MAX - 1;
	int cn = ult - pri + 1;
	// Ajustes del lienzo
	TC->Font->Size = 10;
	TC->Font->Color = clBlack;
	TC->Pen->Width = 1;
	// ancho de celda
	int w = TC->TextWidth("1234567890");
	// altura de celda
	int h = TC->TextHeight("0");
	// mitad de celda
	int mid = w * 0.5;
	// Para limpiar el cuadro de la memoria en cada llamada
	static int ant_size = 0;
	TC->Brush->Color = clClear;
	TC->FillRect(Rect(posX, posY, posX + w * 4 + 2, ant_size));
	ant_size = posY + h * (cn + 3);
	// Escribir la etiqueta LIBRE debajo de la memoria
	AnsiString L = "LIBRE = " + IntToStr(libre);
	TC->TextOut(posX + mid, posY + h * (cn + 2), L);
	// Centrar el texto en la coordenada dada
	SetTextAlign(TC->Handle, TA_CENTER);
	// Escribir las etiquetas o titulos de cada tabla
	TC->TextOut(posX + mid, posY, "DIR");
	TC->TextOut(posX + w + mid, posY, "DATO");
	TC->TextOut(posX + w * 2 + mid, posY, "ID");
	TC->TextOut(posX + w * 3 + mid, posY, "LINK");
	// Definir colores de cada tabla
	// puede crear un TColor con valores en
	// formato Blue, Green, Red:
	//							   |
	//			  				   v
	//					   		 B,G,R
	// TColor naranja = TColor(0x0080FF);
	TColor color[] = { clClear, clLime, clYellow, clYellow };
	// Pintar las tablas

	for (int i = 0; i <= 3; i++) {
		TC->Brush->Color = color[i];
		TC->FillRect(Rect(posX + w * i, posY + h,
						 posX + w * (i + 1), posY + h * (cn + 1)));
	}
	// Escribir los datos de cada tabla
	TC->Brush->Style = bsClear;
	for (int i = 0; i < cn; i++) {
		Dato dato = MEM[pri + i].dato;
		AnsiString id = MEM[pri + i].id.c_str();
		int link = MEM[pri + i].link;
		TC->TextOut(posX + mid, posY + h * (i + 1), i + pri);
		TC->TextOut(posX + w * 1 + mid, posY + h * (i + 1), dato);
		TC->TextOut(posX + w * 2 + mid, posY + h * (i + 1), id);
		TC->TextOut(posX + w * 3 + mid, posY + h * (i + 1), link);
	}
	// Dibujar las lineas de separacion de celdas y bordes
	for (int i = 1; i <= cn+1; i++) {
		TC->MoveTo(posX + w, posY + h * i);
		TC->LineTo(posX + w * 4, posY + h * i);
	}
	for (int i = 1; i <= 4; i++) {
		TC->MoveTo(posX + w * i, posY + h);
		TC->LineTo(posX + w * i, posY + h * (cn + 1));
	}
	ocultarLinks(pri, ult, posX, posY);
	// Establecer el alineamiento de texto a normal
	SetTextAlign(TC->Handle, TA_LEFT);
}
