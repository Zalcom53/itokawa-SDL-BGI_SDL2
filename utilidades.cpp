
#include "utilidades.h"
void LeerFormatoA(string NombreArchivo){
    ifstream archivo;
    archivo.open(NombreArchivo.c_str());
    string linea;
    // se crea una matriz de 3 x la longitud del archivo

    int Renglones_V = 0;
    while (getline(archivo, linea) && linea[0] == 'v')
    {
        Renglones_V++;
    }

    int Renglones_F = 0;
    /*tenemos que verificar que si los vertices empiezan en 1... ya que si se abre un archivo
    y empieza en 0 uno de los puntos de su vertices, pues no podríamos acceder a su índice, debido que
    para acceder al índice, se utiliza la formula n-1. Que es así como está en el archivo
    */
    bool pIniZero = false;
    string t;
    string p = " 0 ";
    double x, y, z;
    do
    {
        Renglones_F++; 
        if (linea.find(p) != string::npos) pIniZero = true;
    } while (getline(archivo, linea));
    
    double **Puntos_V = CrearMatriz(Renglones_V, 3);
    double **Puntos_F = CrearMatriz(Renglones_F, 3);
    archivo.clear();
    archivo.seekg(0, ios::beg);

    // Se llena la matriz de los puntos V
    for (int i = 0; i < Renglones_V; i++)
    {
        archivo >> t >> x >> y >> z;
        Puntos_V[i][0] = x;
        Puntos_V[i][1] = y;
        Puntos_V[i][2] = z;
    }
    
    // Se llena la matriz de los puntos F
    for (int i = 0; i < Renglones_F; i++)
    {
        archivo >> t >> x >> y >> z;  
        Puntos_F[i][0] = x + int(pIniZero);
        Puntos_F[i][1] = y + int(pIniZero);
        Puntos_F[i][2] = z + int(pIniZero);
    }
    archivo.close();

    cout << "Se va a graficar..." << endl
         << endl;
    system("pause");
    GraficarTipoA(Puntos_V, Puntos_F, Renglones_V, Renglones_F);
    EliminarMatriz(Puntos_V);
    EliminarMatriz(Puntos_F);
}
void LeerFormatoB(string NombreArchivo)
{
	fstream inFile(NombreArchivo.c_str());
    int filas = count(std::istreambuf_iterator<char>(inFile), 
             std::istreambuf_iterator<char>(), '\n');

	
	double **Puntos_V = CrearMatriz(filas * 3, 3);
    double **Puntos_F = CrearMatriz(filas * 3, 3);
	
	double x1,x2,x3,y1,y2,y3,z1,z2,z3;
	string t;
	ifstream archivo;
    archivo.open(NombreArchivo.c_str());
    string linea;	
    for(int i = 0; i < filas; i++)
	{
		int j = i*3;
    	archivo >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3 >> t;
        Puntos_V[j][0] = x1;
        Puntos_V[j][1] = y1;
        Puntos_V[j][2] = z1;
		
		Puntos_V[j+1][0] = x2;
        Puntos_V[j+1][1] = y2;
        Puntos_V[j+1][2] = z2;
		
		Puntos_V[j+2][0] = x3;
        Puntos_V[j+2][1] = y3;
        Puntos_V[j+2][2] = z3;
		
		Puntos_F[j][0] = j+1;
        Puntos_F[j][1] = j+2;
        Puntos_F[j][2] = j+3;
        
        Puntos_F[j+1][0] = j+1;
        Puntos_F[j+1][1] = j+2;
        Puntos_F[j+1][2] = j+3;
        
        Puntos_F[j+2][0] = j+1;
        Puntos_F[j+2][1] = j+2;
        Puntos_F[j+2][2] = j+3;
	}
    archivo.close();
    
    cout << "Se va a graficar..." << endl
         << endl;
    system("pause");
    GraficarTipoA(Puntos_V, Puntos_F, filas*3, filas*3);
    EliminarMatriz(Puntos_V);
    EliminarMatriz(Puntos_F);
}

double **CrearMatriz(int m, int n)
{
    double **Matriz = NULL;
    Matriz = new double *[m];
    Matriz[0] = new double[m * n];
    for (int i = 1; i < m; ++i)
        Matriz[i] = Matriz[i - 1] + n;
    return Matriz;
}

void EliminarMatriz(double **&matriz)
{
    delete[] matriz[0];
    delete[] matriz;
    matriz = NULL;
}
