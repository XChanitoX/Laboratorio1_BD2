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
}

AlumnoCM::AlumnoCM(std::string codigo, std::string nombre, std::string apellidos, std::string carrera, int ciclo,
                   float mensualidad) : _ciclo(ciclo), _mensualidad(mensualidad) {
    for (size_t i = 0; i < 5; ++i)
        _codigo[i] = codigo[i];

    for (size_t i = 0; i < 11; ++i)
        _nombre[i] = nombre[i];

    for (size_t i = 0; i < 20; ++i)
        _apellidos[i] = apellidos[i];

    for (size_t i = 0; i < 15; ++i)
        _carrera[i] = carrera[i];
}

FixedRecordBin::FixedRecordBin(std::string filename) : _filename(std::move(filename)) {}

std::vector<AlumnoCM> FixedRecordBin::load() {

    return std::vector<AlumnoCM>();
}

void FixedRecordBin::add(AlumnoCM record) {
    std::ofstream file(_filename, std::ios::out | std::ios::binary | std::ios::ate);
    file.write(reinterpret_cast<const char *>(&record), sizeof(AlumnoCM));
    file.close();
}

AlumnoCM FixedRecordBin::readRecord(int pos) {
    std::ifstream file(_filename, std::ios::in | std::ios::binary);
    file.seekg(pos * (sizeof(AlumnoCM) + 1), std::ios::beg);

    AlumnoCM newAlumno{};
    file.read(reinterpret_cast<char *>(&newAlumno), sizeof(AlumnoCM));

    file.close();
    return newAlumno;
}

bool FixedRecordBin::remove(int pos) {
    return false;
}
