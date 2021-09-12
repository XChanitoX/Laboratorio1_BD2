#include <iostream>
#include "FixedRecord.h"
#include "FixedRecordBin.h"

using namespace std;

int main() {
//    FixedRecord funcionPrincipal = FixedRecord("../archivos/datos1.txt");
//
//    cout << "Probando funcion load:" << endl;
//    vector<Alumno> alumnos = funcionPrincipal.load();
//
//    cout << endl << "Probando funcion add:" << endl;
//
//    cout << endl << "Probando funcion readRecord:" << endl;
//    cout << "Imprimiendo el registro del alumno 3: " << endl;
//    Alumno alumno1 = Alumno();
//    alumno1 = funcionPrincipal.readRecord(2);
//    alumno1.imprimir();

    cout << "=== P2 ===\n";

    FixedRecordBin fixedRecordBin("../archivos/P2.bin");

    AlumnoCM alumno01("0001", "Howard", "Paredes Zegarra", "Computacion", 5, 100.50);
    AlumnoCM alumno02("0002", "Penny", "Vargas Cordero", "Industrial", 10, 1200.55);
    AlumnoCM alumno03("0003", "Sheldon", "Cooper Vega", "Mecatronica", 2, 500.75);

    fixedRecordBin.add(alumno01);
    fixedRecordBin.add(alumno02);
    fixedRecordBin.add(alumno03);

    AlumnoCM alumnoRec = fixedRecordBin.readRecord(1);

    cout << alumnoRec._codigo << '\n';
    cout << alumnoRec._nombre << '\n';
    cout << alumnoRec._apellidos << '\n';
    cout << alumnoRec._carrera << '\n';
    cout << alumnoRec._ciclo << '\n';
    cout << alumnoRec._mensualidad << '\n';

    cout << "Todo se ejecuto correctamente\n";

    return 0;
}