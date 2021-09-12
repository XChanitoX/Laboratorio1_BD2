#include <iostream>
#include "FixedRecord.h"

using namespace std;

int main(){
    FixedRecord funcionPrincipal = FixedRecord("../archivos/datos1.txt");

    cout << endl << "-------------------load-----------------" << endl;
    vector<Alumno> alumnos = funcionPrincipal.load();
    cout << "Imprimiendo los registros de los alumnos 2,4,6: " << endl << endl;
    alumnos[1].imprimir();
    alumnos[3].imprimir();
    alumnos[5].imprimir();

    /*
    cout << "-------------------add------------------" << endl;
    Alumno alumnoA = Alumno();
    string codigo, nombre, apellidos, carrera;
    codigo = "0007 ";
    nombre = "Heider     ";
    apellidos = "Sanchez Quizpe      ";
    carrera = "Mecatronica    ";
    alumnoA.asignarValores(codigo,nombre,apellidos,carrera);
    funcionPrincipal.add(alumnoA);*/

    cout << endl << "----------------readRecord--------------" << endl;
    cout << "Imprimiendo el registro del alumno 3: " << endl;
    Alumno alumnoB = Alumno();
    alumnoB = funcionPrincipal.readRecord(2);
    alumnoB.imprimir();

    return 0;
}