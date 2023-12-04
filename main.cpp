#include <iostream>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> // Para usleep
#include <math.h>
#include <time.h>

#include "proyecciones.h"
#include "utilidades.h"

using namespace std;

int main(){
    int Op;

    do{
        // MENU
        cout << "Graficar Craneo [1]" << endl;
        cout << "Graficar Cactus [2]" << endl;
        cout << "Graficar Asteroide Eros [3]" << endl;
        cout << "Graficar Asteroide Geographos [4]" << endl;
        cout << "Graficar Asteroide Itokawa [5]" << endl;
        cout << "Salir [0]" << endl;

        do{
            cout << "Elija Opción: ";
            cin >> Op;
            if (Op < 0 || Op > 5)
                cout << "Fuera de Rango..." << endl;
        } while (Op < 0 || Op > 5);

        if (Op == 0){
            sleep(1); // Pausa de 1 segundo en Linux
            return 0;
        }

        system("clear"); // En Linux, utiliza "clear" para limpiar la consola

        switch (Op){
        case 1:
            LeerFormatoA("OBJETOS-3D/QueSoy1.obj");
            sleep(1);
            break;
        case 2:
            LeerFormatoA("OBJETOS-3D/QueSoy2.obj");
            sleep(1);
            break;
        case 3:
            LeerFormatoA("OBJETOS-3D/eros022540.tab");
            sleep(1);
            break;
        case 4:
            LeerFormatoA("OBJETOS-3D/1620geographos.tab");
            sleep(1);
            break;
        case 5:
            LeerFormatoB("OBJETOS-3D/itokawa_f0049152.tri");
            sleep(1);
            break;
        }

        system("clear");

    } while (Op != 0);

    return 0;
}
