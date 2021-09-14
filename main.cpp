#include <iostream>
#include "FixedRecord.h"
#include <cassert>
#include "FixedRecordBin.h"
#include "VariableRecordBin.h"

using namespace std;

int main() {
//    string fileName = "../archivos/datos1.txt";
//    FixedRecord funcionPrincipal = FixedRecord(fileName);
//
//    cout << endl << "-------------------load-----------------" << endl;
//    vector<Alumno> alumnos = funcionPrincipal.load();
//    cout << "Imprimiendo los registros de los alumnos 2,4,6: " << endl << endl;
//    alumnos[1].imprimir();
//    alumnos[3].imprimir();
//    alumnos[5].imprimir();
//
//    cout << "-------------------add------------------" << endl;
//    Alumno alumnoA = Alumno();
//    std::string codigo, nombre, apellidos, carrera;
//    codigo = "0008";
//    nombre = "Luis";
//    apellidos = "Ango Rivera";
//    carrera = "Bioingenieria";
//    alumnoA.asignarValores(codigo, nombre, apellidos, carrera);
//    funcionPrincipal.add(alumnoA);
//    cout << "Alumno agregado con exito." << endl;
//
//
//    cout << endl << "----------------readRecord--------------" << endl;
//    cout << "Imprimiendo el registro del alumno 3: " << endl;
//    Alumno alumnoB;
//    alumnoB = funcionPrincipal.readRecord(2);
//    alumnoB.imprimir();
//
//
//    cout << "=== P2 ===\n";
//
//    /* Conviene usar un archivo binario para reducir el peso del archivo. Guardar un número entero como una cadena de
//     * caracteres puede consumir muchos bytes cuando en binario ocuparía 4 bytes. Las operaciones para leer y escribir
//     * son mucho más limpias.*/
//
//    cout << "Test 01" << '\n';
//
//    FixedRecordBin frb01("../archivos/P2.bin");
//
//    AlumnoCM alumno01("0001", "Howard", "Paredes Zegarra", "Computacion", 5, 100.50);
//    AlumnoCM alumno02("0002", "Penny", "Vargas Cordero", "Industrial", 10, 1200.55);
//    AlumnoCM alumno03("0003", "Sheldon", "Cooper Vega", "Mecatronica", 2, 500.75);
//
//    frb01.add(alumno01);
//    frb01.add(alumno02);
//    frb01.add(alumno03);
//
//    AlumnoCM alumnoRec = frb01.readRecord(2);
//    assert(std::string(alumnoRec._codigo) == "0003");
//
//    cout << "Test 02" << '\n';
//
//    FixedRecordBin frb02("../archivos/P2.bin");
//
//    auto records02 = frb02.load();
//
//    assert(std::string(records02[1]._nombre) == "Penny");
//
//    cout << "Test 03" << '\n';
//
//    FixedRecordBin frb03("../archivos/P2.bin");
//
//    frb03.remove(0);
//    frb03.remove(2);
//
//    auto records03 = frb03.load();
//
//    assert(records03[0]._nextDelete == -2);
//    assert(records03[2]._nextDelete == 0);
//
//    AlumnoCM alumno06("0006", "Jesus", "Vega Cordero", "Mecatronica", 8, 10.50);
//    frb03.add(alumno06);
//
//    records03 = frb03.load();
//
//    assert(std::string(records03[2]._nombre) == "Jesus");
//
//    AlumnoCM alumno07("0007", "Heider", "Sanchez Quizpe", "Mecatronica", 3, 1.50);
//    frb03.add(alumno07);
//
//    records03 = frb03.load();
//
//    assert(std::string(records03[0]._nombre) == "Heider");
//
//    AlumnoCM alumno05("0005", "Vanesa", "Cooper Quizpe", "Mecatronica", 7, 890.85);
//    frb03.add(alumno05);
//
//    records03 = frb03.load();
//
//    assert(std::string(records03[3]._nombre) == "Vanesa");
//
//    cout << "Todo se ejecuto correctamente\n";

    cout << "=== P4 ===\n";


    VariableRecordBin vrb01("../archivos/P4.bin");

    Matricula matricula01 = {"000", 3, 100.2, "No pago"};
    vrb01.add(matricula01);

    auto record = vrb01.readRecord(0);

    assert(record._observaciones == matricula01._observaciones);

    Matricula matricula02 = {"001", 5, 129.20, "Todo bien"};
    Matricula matricula03 = {"002", 9, 1.20, "Todo mal"};
    vrb01.add(matricula02);
    vrb01.add(matricula03);

    auto records = vrb01.load();

    for (const auto &r :records)
        cout << r._codigo << ' ' << r._ciclo << ' ' << r._mensualidad << ' ' << r._observaciones << '\n';

    assert(records[0]._ciclo == 3);
    assert(abs(records[1]._mensualidad - matricula02._mensualidad) < 1e6);
    assert(records[2]._observaciones == "Todo mal");

    cout << "Todo se ejecuto correctamente\n";
}