#ifndef PROYECCIONES_H_INCLUDED
#define PROYECCIONES_H_INCLUDED

#include <iostream>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> // Para usleep
#include <math.h>
#include "utilidades.h"

using namespace std;

enum opcionesOrto{XY = 1, XZ, YZ};

void GraficarTipoA(const double * const *Matriz_Puntos_V, const double * const *Matriz_Puntos_F, const int tam_V, const int tam_F);

double **ViewPort(const double *const *matriz, const int tam, const double Xmin, const double Xmax, const double Ymin, const double YMax, const double Umin, const double Umax, const double Vmin, const double VMax);

void dibujar(const double *const *matriz, const double *const *matriz_lineas, const int tam_V, const int tam_F);

double **CalcOrtografica(const double *const *Matriz_Puntos_V,const int tam_V, const int opOrto);

double **CalcAxonIso(const double *const *Matriz_Puntos_V, const int tam_V);

#endif // PROYECCIONES_H_INCLUDED
