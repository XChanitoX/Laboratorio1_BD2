#include <iostream>
#include "FixedRecord.h"

using namespace std;

int main(){
    FixedRecord funcionPrincipal = FixedRecord("../archivos/datos1.txt");

    cout << "Probando funcion load:" << endl;
    vector<Alumno> alumnos = funcionPrincipal.load();

    cout << endl << "Probando funcion add:" << endl;

    cout << endl << "Probando funcion readRecord:" << endl;
    cout << "Imprimiendo el registro del alumno 3: " << endl;
    Alumno alumno1 = Alumno();
    alumno1 = funcionPrincipal.readRecord(2);
    alumno1.imprimir();

    return 0;
}