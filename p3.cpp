#include <iostream>
#include "VariableRecord.h"

using namespace std;

int main(){
    string fileName = "../archivos/datos2.txt";
    VariableRecord funcionPrincipal = VariableRecord(fileName);

    cout << endl << "-------------------load-----------------" << endl;
    vector<Alumno> alumnos = funcionPrincipal.load();
    cout << "Imprimiendo los registros de los alumnos 1,2,3: " << endl << endl;
    alumnos[1].imprimir();
    alumnos[2].imprimir();
    alumnos[3].imprimir();
/*
    cout << "-------------------add------------------" << endl;
    Alumno alumnoA = Alumno();
    std::string codigo, nombre, apellidos, carrera;
    codigo = "0008";
    nombre = "Luis";
    apellidos = "Ango Rivera";
    carrera = "Bioingenieria";
    alumnoA.asignarValores(codigo, nombre, apellidos, carrera);
    funcionPrincipal.add(alumnoA);
    cout << "Alumno agregado con exito." << endl;


    cout << endl << "----------------readRecord--------------" << endl;
    cout << "Imprimiendo el registro del alumno 3: " << endl;
    Alumno alumnoB;
    alumnoB = funcionPrincipal.readRecord(2);
    alumnoB.imprimir();
*/
    return 0;
}