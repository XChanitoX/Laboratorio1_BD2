//
// Created by ceduardosq on 9/12/21.
//

#include "FixedRecordBin.h"

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
