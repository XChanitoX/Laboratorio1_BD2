//
// Created by ceduardosq on 9/12/21.
//

#ifndef LABORATORIO1_DB2_FIXEDRECORDBIN_H
#define LABORATORIO1_DB2_FIXEDRECORDBIN_H

#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <cstring>

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


#endif //LABORATORIO1_DB2_FIXEDRECORDBIN_H
