#include <iostream>
#include "FixedRecord.h"

using namespace std;

int main(){
    FixedRecord funcionPrincipal = FixedRecord("../archivos/datos1.txt");
    cout << "Probando funcion load:" << endl;
    vector<Alumno> alumnos = funcionPrincipal.load();
    cout << "Imprimiendo los alumnos del archivo..." << endl;


    cout << "Probando funcion add:" << endl;


    cout << "Probando funcion readRecord:" << endl;

    return 0;
}