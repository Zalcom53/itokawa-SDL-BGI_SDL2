#include "proyecciones.h"
void GraficarTipoA(const double *const *Matriz_Puntos_V, const double *const *Matriz_Puntos_F, const int tam_V, const int tam_F){
    initwindow(800, 800, "Recta");

    int cenX = getmaxx() / 2;
    int cenY = getmaxy() / 2;
    /* Se pintan los ejes X y Y */
    setcolor(WHITE);
    line(0, cenY, getmaxx(), cenY);
    line(cenX, 0, cenX, getmaxy());

    /*
    Se crea una matriz dinámica para almacenar los puntos de la figura
    El programa dibujará 4 diferentes perspectivas de la figura, por ende, se tendrá que modificar 4 veces la matriz de puntos
    ┌──────────────────┬──────────────────┐
    │                  │                  │
    │                  │                  │
    │   Ortogáfica XY  │  Ortogáfica XZ   │
    │       #1         │        #2        │
    │                  │                  │
    ├──────────────────┼──────────────────│
    │                  │    proyección    │
    │   Ortogáfica YZ  │    axonométrica  │
    │       #3         │    isométrica    │
    │                  │       #4         │
    │                  │                  │
    └──────────────────┴──────────────────┘
    */
    double **Matriz_T = CrearMatriz(tam_V, 3);

    //PESPECTIVA 1 *Ortogáfica XY*
    Matriz_T = CalcOrtografica(Matriz_Puntos_V, tam_V, XY);
    dibujar(Matriz_T, Matriz_Puntos_F, tam_V, tam_F);

    //PESPECTIVA 2 *Ortogáfica XZ*
    Matriz_T = CalcOrtografica(Matriz_Puntos_V, tam_V, XZ);
    dibujar(Matriz_T, Matriz_Puntos_F, tam_V, tam_F);

    //PESPECTIVA 3 *Ortogáfica YZ*
    Matriz_T = CalcOrtografica(Matriz_Puntos_V, tam_V, YZ);
    dibujar(Matriz_T, Matriz_Puntos_F, tam_V, tam_F);

    //PESPECTIVA 4 *Proyección axonométrica isométrica*
    Matriz_T = CalcAxonIso(Matriz_Puntos_V, tam_V);
    dibujar(Matriz_T, Matriz_Puntos_F, tam_V, tam_F);

    //Se abre la ventana para mostrar la gráfica
    getch();
    closegraph();

    //se elimina la matriz creada en memoria dinámica
    EliminarMatriz(Matriz_T);
}


    /*
    Función que calcula la matriz para el ViewPort...
    Se aplican las fórmulas explicadas en clase y nos retorna la matriz
    que se va a utilizar para dibujar la figura ya aplicado el viewport

    ¿Qué es viewport?
    Es la escala de visualización, es decir, el área en la que se dibuja la figura.
    En este caso, lo necesitamos ya que al ser una ventana de 800x800, lo divimos en 4 fracciones.
    Por ende, necesitamos aplicar viewport para que se ajuste su escala y posición a la posición de la ventana especificada.
    */
double **ViewPort(const double *const *matriz, const int tam, const double Xmin, const double Xmax, const double Ymin, const double Ymax, const double Umin, const double Umax, const double Vmin, const double Vmax){
    double **matrizT = CrearMatriz(tam, 2);
    for (int i = 0; i < tam; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            matrizT[i][0] = matriz[i][0] * ((Umax - Umin) / (Xmax - Xmin)) + (Umin - (((Umax - Umin) * Xmin) / (Xmax - Xmin)));
            matrizT[i][1] = matriz[i][1] * ((Vmax - Vmin) / (Ymax - Ymin)) + (Vmin - (((Vmax - Vmin) * Ymin) / (Ymax - Ymin)));
        }
    }
    return matrizT;
}

    /*
    Función para dibujar todos los puntos de la matriz.
    Además de dibujar los puntos, va a dibujar las lineas contenidas en la matriz_lineas
    */
void dibujar(const double *const *matriz, const double *const *matriz_lineas, const int tam_V, const int tam_F){
    setcolor(15);
    for (int i = 0; i < tam_V; i++){
        putpixel(matriz[i][0], matriz[i][1], WHITE);
    }

    double a_X, a_Y, b_X, b_Y, c_X, c_Y;
    int ia, ib, ic;

    for (int i = 0; i < tam_F; i++){
        ia =  matriz_lineas[i][0]-1;
        ib =  matriz_lineas[i][1]-1;
        ic =  matriz_lineas[i][2]-1;

        a_X = matriz[ia][0];
        a_Y = matriz[ia][1];

        b_X = matriz[ib][0];
        b_Y = matriz[ib][1];

        c_X = matriz[ic][0];
        c_Y = matriz[ic][1];

        setcolor(15);
        line(a_X, a_Y, b_X, b_Y);
        line(a_X, a_Y, c_X, c_Y);
        line(b_X, b_Y, c_X, c_Y);
    }

}

/*
    Función para calcular la proyección ortografica de la matriz de puntos pasada por parametros.
    El cuatro parámetro "opOrto" se utilizó para determinar la proyección a realizar. Gracias a esto, se ahorra mucho código repetido
*/
double **CalcOrtografica(const double *const *Matriz_Puntos_V, const int tam_V, const int opOrto){
    double **Matriz_T = CrearMatriz(tam_V, 3);
    int variableA = 0;
    int variableB = 1;

    if (opOrto == XZ) variableB = 2;

    if (opOrto == YZ){
        variableA = 1;
        variableB = 2;
    }

    //Se calculará el mayor y el minimo de la matriz de puntos
    //El objetivo de esto, es hacer un cuadro delimitador para determinar el viewport
    double minX = Matriz_Puntos_V[0][variableA];
    // la coordenada Y en el minimo X
    double minX_Y = Matriz_Puntos_V[0][variableB];

    double maxX = Matriz_Puntos_V[0][variableA];
    // la coordenada Y en el maximo X
    double maxX_Y = Matriz_Puntos_V[0][variableB];

    double minY = Matriz_Puntos_V[0][variableB];
    // la coordenada X en el minimo Y
    double minY_X = Matriz_Puntos_V[0][variableA];

    double maxY = Matriz_Puntos_V[0][variableB];
    // la coordenada x en el maximo Y
    double maxY_X = Matriz_Puntos_V[0][variableA];

    for (int i = 0; i < tam_V; i++){
        for (int j = 0; j < 3; j++){
            Matriz_T[i][j] = Matriz_Puntos_V[i][j];
        }

        switch (opOrto){
        case XY:
            break;

        case XZ:
            // X = X
            // Y = Z
            Matriz_T[i][1] = Matriz_T[i][2];
            break;

        case YZ:
            //X = Y
            //Y = Z
            Matriz_T[i][0] = Matriz_T[i][1];
            Matriz_T[i][1] = Matriz_T[i][2];
            break;
        }

        Matriz_T[i][2] = 0;

        if (Matriz_T[i][0] < minX){
            minX = Matriz_T[i][0];
            minX_Y = Matriz_T[i][1];
        }
        if (Matriz_T[i][0] > maxX)
        {
            maxX = Matriz_T[i][0];
            maxX_Y = Matriz_T[i][1];
        }

        if (Matriz_T[i][1] < minY){
            minY = Matriz_T[i][1];
            minY_X = Matriz_T[i][0];
        }

        if (Matriz_T[i][1] > maxY){
            maxY = Matriz_T[i][1];
            maxY_X = Matriz_T[i][0];
        }
    }

    double long_X = maxX - minX;
    double long_Y = maxY - minY;
    double margen = 0.1;
    if (long_X >= long_Y){
        margen = long_X * 0.05;
        minX -= margen;
        minY = minX_Y - (long_X / 2) - margen;
        maxX += margen;
        maxY = maxX_Y + (long_X / 2) + margen;
    }
    else
    {
        margen = long_Y * 0.05;
        minY -= margen;
        minX = minY_X - (long_Y / 2) - margen;
        maxY += margen;
        maxX = maxY_X + (long_Y / 2) + margen;
    }

    // Windows a viewport
    switch (opOrto)
        {
        case XY:
            Matriz_T = ViewPort(Matriz_T, tam_V, minX, maxX, minY, maxY, 0, 400, 400, 0);
            break;

        case XZ:
            Matriz_T = ViewPort(Matriz_T, tam_V, minX, maxX, minY, maxY, 400, 800, 400, 0);
            break;

        case YZ:
            Matriz_T = ViewPort(Matriz_T, tam_V, minX, maxX, minY, maxY, 0, 400, 800, 400);
            break;
        }

    return Matriz_T;

}
/*
    Función para calcular la proyección axonometrica isométrica de la matriz de puntos pasada por parámetros.
*/
double **CalcAxonIso(const double *const *Matriz_Puntos_V, const int tam_V)
{
    double **Matriz_T = CrearMatriz(tam_V, 3);

    double a,b,c;

    for (int i = 0; i < tam_V; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            Matriz_T[i][j] = Matriz_Puntos_V[i][j];
        }
    }
    a = b = c = 1;
    //a = 1;
    //b = 1;
    //c = 1;
    double minX, maxX, minY, maxY, minY_X, maxY_X, minX_Y, maxX_Y;
    for (int i = 0; i < tam_V; i++)
    {
        Matriz_T[i][0] = (Matriz_T[i][0] * (c/sqrt((a*a)+(c*c)))) - (Matriz_T[i][2] * (a/sqrt((a*a)+(c*c))));
        Matriz_T[i][1] = (Matriz_T[i][0] * (-(a*b) / (sqrt((a*a)+(c*c)) * sqrt((a*a)+(b*b)+(c*c))))) +
                             (Matriz_T[i][1] * ((sqrt((a*a)+(c*c))) / (sqrt((a*a)+(b*b)+(c*c))))) -
                             (Matriz_T[i][2] * (c*b) / (sqrt((a*a)+(c*c)) * sqrt((a*a)+(b*b)+(c*c))));
        Matriz_T[i][2] = 0;
        if(i == 0){
            minX = maxX = minY_X = maxY_X = Matriz_T[0][0];
            minY = maxY = minX_Y = maxX_Y = Matriz_T[0][1];
        }
        if (Matriz_T[i][0] < minX)
        {
            minX = Matriz_T[i][0];
            minX_Y = Matriz_T[i][1];
        }
        if (Matriz_T[i][0] > maxX)
        {
            maxX = Matriz_T[i][0];
            maxX_Y = Matriz_T[i][1];
        }

        if (Matriz_T[i][1] < minY)
        {
            minY = Matriz_T[i][1];
            minY_X = Matriz_T[i][0];
        }

        if (Matriz_T[i][1] > maxY)
        {
            maxY = Matriz_T[i][1];
            maxY_X = Matriz_T[i][0];
        }
    }

    double long_X = maxX - minX;
    double long_Y = maxY - minY;
    double margen = 0.1;
    if (long_X >= long_Y)
    {
        margen = long_X * 0.05;
        minX -= margen;
        minY = minX_Y - (long_X / 2) - margen;
        maxX += margen;
        maxY = maxX_Y + (long_X / 2) + margen;
    }
    else
    {
        margen = long_Y * 0.05;
        minY -= margen;
        minX = minY_X - (long_Y / 2) - margen;
        maxY += margen;
        maxX = maxY_X + (long_Y / 2) + margen;
    }

    Matriz_T = ViewPort(Matriz_T, tam_V, minX, maxX, minY, maxY, 400, 800, 800, 400);

    return Matriz_T;
}
