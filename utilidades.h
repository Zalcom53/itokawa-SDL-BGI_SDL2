#ifndef UTILIDADES_H_INCLUDED
#define UTILIDADES_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include "proyecciones.h"
using namespace std;

void LeerFormatoA(string NombreArchivo);
void LeerFormatoB(string NombreArchivo);

double **CrearMatriz(int m, int n);

void EliminarMatriz(double **&matriz);

#endif // UTILIDADES_H_INCLUDED
