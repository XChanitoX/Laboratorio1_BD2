#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <cstring>

using namespace std;

struct AlumnoCM {
    char _codigo[5];
    char _nombre[11];
    char _apellidos[20];
    char _carrera[15];

    int _ciclo;
    float _mensualidad;

    int _nextDelete;

    AlumnoCM();

    AlumnoCM(std::string _codigo, std::string _nombre, std::string _apellidos, std::string _carrera, int ciclo,
             float mensualidad, int nextDelete = -1);

    void setNextDelete(int nextDelete);
};

class FixedRecordBin {
    std::string _filename{};

public:
    FixedRecordBin(std::string filename);

    std::vector<AlumnoCM> load();

    void add(AlumnoCM record);

    AlumnoCM readRecord(int pos);

    bool remove(int pos);
};

AlumnoCM::AlumnoCM() {
    std::memset(_codigo, ' ', 5);
    std::memset(_nombre, ' ', 5);
    std::memset(_apellidos, ' ', 11);
    std::memset(_carrera, ' ', 20);
    _ciclo = 0;
    _mensualidad = 0;
    _nextDelete = -1;
}

AlumnoCM::AlumnoCM(std::string codigo, std::string nombre, std::string apellidos, std::string carrera, int ciclo,
                   float mensualidad, int nextDelete) : _ciclo(ciclo), _mensualidad(mensualidad),
                                                        _nextDelete(nextDelete) {
    for (size_t i = 0; i < 5; ++i)
        _codigo[i] = codigo[i];

    for (size_t i = 0; i < 11; ++i)
        _nombre[i] = nombre[i];

    for (size_t i = 0; i < 20; ++i)
        _apellidos[i] = apellidos[i];

    for (size_t i = 0; i < 15; ++i)
        _carrera[i] = carrera[i];
}

void AlumnoCM::setNextDelete(int nextDelete) {
    _nextDelete = nextDelete;
}

FixedRecordBin::FixedRecordBin(std::string filename) : _filename(std::move(filename)) {
    std::fstream file(_filename, std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);

    size_t a = file.tellg();
    if (file.tellg() == 0) {
        int k = -2;
        file.seekp(0);
        file.write(reinterpret_cast<const char *>(&k), sizeof(int));
    }

    file.close();
}

std::vector<AlumnoCM> FixedRecordBin::load() {
    std::ifstream file(_filename, std::ios::in | std::ios::binary | std::ios::ate);
    int size = (int) file.tellg() - sizeof(int), nRegisters = size / sizeof(AlumnoCM);

    file.seekg(sizeof(int), std::ios::beg);

    std::vector<AlumnoCM> answer(nRegisters);

    for (size_t i = 0; i < answer.size(); ++i)
        file.read(reinterpret_cast<char *>(&answer[i]), sizeof(AlumnoCM));

    file.close();
    return answer;
}

void FixedRecordBin::add(AlumnoCM record) {
    std::fstream file(_filename, std::ios::in | std::ios::out | std::ios::binary);
    int k{};
    file.read(reinterpret_cast<char *>(&k), sizeof(int));
    if (k == -2) {
        file.seekp(0, std::ios::end);
        file.write(reinterpret_cast<char *>(&record), sizeof(AlumnoCM));
    } else {
        file.seekg(k * sizeof(AlumnoCM) + sizeof(int), std::ios::beg);
        AlumnoCM alumnno{};
        file.read(reinterpret_cast<char *>(&alumnno), sizeof(alumnno));

        file.seekp(0, std::ios::beg);
        file.write(reinterpret_cast<char *>(&alumnno._nextDelete), sizeof(int));

        file.seekp(k * sizeof(AlumnoCM) + sizeof(int), std::ios::beg);
        file.write(reinterpret_cast<const char *>(&record), sizeof(AlumnoCM));
    }
    file.close();
}

AlumnoCM FixedRecordBin::readRecord(int pos) {
    std::ifstream file(_filename, std::ios::in | std::ios::binary);
    file.seekg(pos * (sizeof(AlumnoCM)) + sizeof(int), std::ios::beg);

    AlumnoCM newAlumno{};
    file.read(reinterpret_cast<char *>(&newAlumno), sizeof(AlumnoCM));

    file.close();
    return newAlumno;
}

bool FixedRecordBin::remove(int pos) {
    std::fstream file(_filename, std::ios::in | std::ios::out | std::ios::binary);

    int k{};
    file.read(reinterpret_cast<char *>(&k), sizeof(int));
    file.seekg(pos * sizeof(AlumnoCM) + sizeof(int), std::ios::beg);
    AlumnoCM del{};
    file.read(reinterpret_cast<char *>(&del), sizeof(AlumnoCM));
    if (del._nextDelete != -1) return false;

    file.seekp(0, std::ios::beg);
    file.write(reinterpret_cast<char *>(&pos), sizeof(int));
    file.seekp(pos * sizeof(AlumnoCM) + sizeof(int), std::ios::beg);
    del.setNextDelete(k);
    file.write(reinterpret_cast<char *>(&del), sizeof(AlumnoCM));

    file.close();
    return true;
}

int main() {

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

    frb03.remove(0);
    frb03.remove(2);

    auto records03 = frb03.load();

    assert(records03[0]._nextDelete == -2);
    assert(records03[2]._nextDelete == 0);

    AlumnoCM alumno06("0006", "Jesus", "Vega Cordero", "Mecatronica", 8, 10.50);
    frb03.add(alumno06);

    records03 = frb03.load();

    assert(std::string(records03[2]._nombre) == "Jesus");

    AlumnoCM alumno07("0007", "Heider", "Sanchez Quizpe", "Mecatronica", 3, 1.50);
    frb03.add(alumno07);

    records03 = frb03.load();

    assert(std::string(records03[0]._nombre) == "Heider");

    AlumnoCM alumno05("0005", "Vanesa", "Cooper Quizpe", "Mecatronica", 7, 890.85);
    frb03.add(alumno05);

    records03 = frb03.load();

    assert(std::string(records03[3]._nombre) == "Vanesa");

    cout << "Todo se ejecuto correctamente\n";

}