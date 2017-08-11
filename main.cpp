#include <iostream>
#include "stdio.h"
#include <string.h>
#include <time.h>

using namespace std;

// Punto 1)
struct Alumno {
    char nombre[30+1]="";
    char apellido[30+1]="";
    int nroLegajo;
    char especialidad;
};

struct Inscripcion {
    int nroRegional;
    char especialidad;
    Alumno alumno;
    int codMateria;
};

//Punto 2 - Definir prototipo funcion
void imprimirInscripciones(Inscripcion []);

// no era necesaria esta función la hago para reutilizarla
void ordenarBurbuja(Inscripcion []);


void listarIncompatibles(Inscripcion []);
int busquedaBinaria(Inscripcion [], int , int );
void llenarDatosInscripciones(Inscripcion []);
void masInformacion(Inscripcion []);


int main() {

    Inscripcion vec[500];

    llenarDatosInscripciones(vec);

    imprimirInscripciones(vec);

    listarIncompatibles(vec);

    masInformacion(vec);

    int buscado = 1313;
    int posicionDelBuscadoEnElVector = busquedaBinaria(vec,buscado,500);

    cout << "La busqueda binaria de " << buscado << " da como primera posicion: " << posicionDelBuscadoEnElVector << endl;

    cout << "El nro Inscripcion del  " << buscado << " es: " << vec[posicionDelBuscadoEnElVector].codMateria << " en la regional: " << vec[posicionDelBuscadoEnElVector].nroRegional << endl;

    cout << "El maximo valor de un int es: " << INT_MAX << endl;

    return 0;
}

// Punto 2) declaracion funcion
void imprimirInscripciones(Inscripcion vec[]){
    // ordenarBurbuja (no era necesario desarrollarlo)
    Inscripcion aux;

    for (int i = 0; i < 500 ; i++) {
        for (int j = 0; j < 500; j++) {
            if(vec[j].codMateria > vec[j+1].codMateria){
                aux = vec[j];
                vec[j] = vec[j+1];
                vec[j+1] = aux;
            }
        }
    }

    // una vez ordenado lo imprimir por salida estandar
    for (int k = 0; k < 500 ; k++) {
        cout << "Inscripcion nº " << k
             << " en la Regional " << vec[k].nroRegional
                << " en la Especialidad " << vec[k].especialidad
                << " en la materia cuyo código es: " << vec[k].codMateria
                << " del Alumno: " << vec[k].alumno.nombre << " " << vec[k].alumno.apellido
                << " y el lejado del mismo es: " << vec[k].alumno.nroLegajo << endl;
    }

}



// Punto 3)
bool esCompatible(Inscripcion unaInscripcion){
    return unaInscripcion.especialidad == unaInscripcion.alumno.especialidad;
}

// esta funcion la agrego yo para la resolucion pero se tomará bien cualquiera de las dos
// ya que estuvo mal redactada la pregunta
void listarIncompatibles(Inscripcion vec[]){
    for (int i = 0; i < 500 ; i++) {
        if (vec[i].especialidad != vec[i].alumno.especialidad){
            cout << "La inscripcion a la materia " << vec[i].codMateria << " del alumno " << vec[i].alumno.nombre << " " << vec[i].alumno.apellido
                 << "no es correcta dado que corresponde a otra especialidad" << endl;
        }
    }
}

// Punto 4)
/* La manera más apropiada técnica era resolverlo con Corte de Control
 * pero también se podría haber hechdo más eficiente mediante un vector de
 * 29 posiciones de Enteros
*/
void masInformacion(Inscripcion vec[]){
    int totalInscriptosPorRegional[29]= {0};

    for (int i = 0; i < 500 ; i++) {
        totalInscriptosPorRegional[ vec[i].nroRegional - 1]++;
    }

    for (int j = 0; j < 29 ; ++j) {
        cout << "La cantidad total de inscriptos de la Regional " << j + 1 << " fue de: " << totalInscriptosPorRegional[j] << endl;
    }

}

// Punto 5
int busquedaBinaria(Inscripcion vec[], int buscado, int tam){

    // PARA HACER UNA BUSQUEDA BINARIA EL ARREGLO DEBE ESTAR ORDENADO POR EL CAMPO O DATO POR EL CUAL BUSCAMOS

    // no era necesario desarrollar la función de ordenamiento burbuja
    ordenarBurbuja(vec);

    // ahora que está ordenado por DNI empiezo a buscar
    int sup, inf, medio=-1;
    inf = 0;
    sup = tam -1;

    while(inf <= sup){

        medio = (inf + sup) / 2;
        if (vec[medio].codMateria == buscado){
            return medio;
        } else if(buscado > vec[medio].codMateria){
            inf = medio  + 1 ;
        }else {
            sup = medio - 1;
        }

    }

    // SI NO ENCUENTRO EL CODIGO DE MATERIA BUSCADO ENTONCES RETORNO LA POSICIÓN EN LA CUAL DEBERÍA ESTAR ES DECIR LA QUE ME PIDEN EN EL EJERCICIO
    return medio;
}

void ordenarBurbuja(Inscripcion vec[]){
    Inscripcion aux;

    for (int i = 0; i < 500 ; i++) {
        for (int j = 0; j < 500; j++) {
            if(vec[j].codMateria > vec[j+1].codMateria){
                aux = vec[j];
                vec[j] = vec[j+1];
                vec[j+1] = aux;
            }
        }
    }


}


void llenarDatosInscripciones(Inscripcion v[]){

    bool primero = true;
    for (int i = 0; i < 500 ; i++) {
        srand(time(NULL)*i);

        v[i].codMateria= rand() % 2340;
        v[i].especialidad = 'K';
        srand(time(NULL)*i);
        v[i].nroRegional = ( rand() % 29 ) + 1;

        if(v[i].nroRegional < 1 || v[i].nroRegional > 29){
            v[i].nroRegional = 13;
        }

        if (i%2==0){
            v[i].alumno.especialidad = 'K';
            strcpy(v[i].alumno.nombre, "Pepe");
            strcpy(v[i].alumno.apellido, "Correcto");
        }else{
            v[i].alumno.especialidad = 'Z';
            strcpy(v[i].alumno.nombre, "Juancho");
            strcpy(v[i].alumno.apellido, "Perdido");
        }

        v[i].alumno.nroLegajo = i;

        if (primero) {
            v[i].codMateria = 1313;
            v[i].alumno.especialidad = 'K';
            primero = false;
        }
        /*
        srand(time(NULL));
        if( i % 2  == 0){
            v[i].codMateria = 1313;
            v[i].alumno.especialidad = 'K';
        } else{
            v[i].codMateria = rand() % i;
        }*/

    }
}


