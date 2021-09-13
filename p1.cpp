#include <iostream>
#include <cassert>
#include "FixedRecord.h"
#include "FixedRecordBin.h"

using namespace std;

int main() {

    cout << "=== P2 ===\n";

    cout << "Test 01" << '\n';

    FixedRecordBin frb01("../archivos/P2.bin");

    AlumnoCM alumno01("0001", "Howard", "Paredes Zegarra", "Computacion", 5, 100.50);
    AlumnoCM alumno02("0002", "Penny", "Vargas Cordero", "Industrial", 10, 1200.55);
    AlumnoCM alumno03("0003", "Sheldon", "Cooper Vega", "Mecatronica", 2, 500.75);

    frb01.add(alumno01);
    frb01.add(alumno02);
    frb01.add(alumno03);

    AlumnoCM alumnoRec = frb01.readRecord(2);
    assert(std::string(alumnoRec._codigo) == "0003");

    cout << "Test 02" << '\n';

    FixedRecordBin frb02("../archivos/P2.bin");

    auto records02 = frb02.load();

    assert(std::string(records02[1]._nombre) == "Penny");

    cout << "Test 03" << '\n';

    FixedRecordBin frb03("../archivos/P2.bin");

    cout << "===" << '\n';
    auto records03 = frb03.load();
    for (const auto &r: records03)
        cout << r._nombre << ' ' << r._nextDelete << '\n';
    cout << "===" << '\n';

    frb03.remove(0);
    frb03.remove(2);

    cout << "===" << '\n';
    records03 = frb03.load();
    for (const auto &r: records03)
        cout << r._nombre << ' ' << r._nextDelete << '\n';
    cout << "===" << '\n';

    AlumnoCM alumno06("0006", "Jesus", "Vega Cordero", "Mecatronica", 8, 10.50);

    frb03.add(alumno06);

    cout << "===" << '\n';
    records03 = frb03.load();
    for (const auto &r: records03)
        cout << r._nombre << ' ' << r._nextDelete << '\n';
    cout << "===" << '\n';

    AlumnoCM alumno07("0007", "Heider", "Sanchez Quizpe", "Mecatronica", 3, 1.50);

    cout << "Todo se ejecuto correctamente\n";
    return 0;
}