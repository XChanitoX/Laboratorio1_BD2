#include <iostream>
#include "VariableRecord.h"

using namespace std;

int main(){
    string fileName = "../archivos/datos2.txt";
    VariableRecord funcionPrincipal = VariableRecord(fileName);

    cout << endl << "-------------------load-----------------" << endl;
    vector<Alumno> alumnos = funcionPrincipal.load();
    cout << "Imprimiendo los registros de los alumnos 1,2,3: " << endl << endl;
    alumnos[0].imprimir();
    alumnos[1].imprimir();
    alumnos[2].imprimir();


    cout << "-------------------add------------------" << endl;
    Alumno alumnoA = Alumno();
    std::string nombre, apellidos, carrera;
    float mensualidad;
    nombre = "Luis";
    apellidos = "Ango Rivera";
    carrera = "Bioingenieria";
    mensualidad = 2200.00;
    alumnoA.asignarValores(nombre, apellidos, carrera, mensualidad);
    funcionPrincipal.add(alumnoA);
    cout << "Alumno agregado con exito." << endl;


    cout << endl << "----------------readRecord--------------" << endl;
    cout << "Tomando como primer elemento el registro en la posicion 0..." << endl;
    cout << "Imprimiendo el registro del alumno en la posicion 1: " << endl;
    Alumno alumnoB;
    alumnoB = funcionPrincipal.readRecord(1);
    alumnoB.imprimir();

    return 0;
}