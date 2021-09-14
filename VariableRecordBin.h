//
// Created by ceduardosq on 9/13/21.
//

#ifndef LABORATORIO1_DB2_VARIABLERECORDBIN_H
#define LABORATORIO1_DB2_VARIABLERECORDBIN_H

#include <string>
#include <vector>
#include <utility>

struct Matricula {
    std::string _codigo{};
    int _ciclo{};
    float _mensualidad{};
    std::string _observaciones{};
};

struct MetaDataMatricula {
    int _pos{};
    int _size{};
};

class VariableRecordBin {
    std::string _filename{};
    std::string _metafilename{};

public:
    VariableRecordBin(std::string filename);

    std::vector<Matricula> load();

    void add(Matricula record);

    Matricula readRecord(int pos);
};


#endif //LABORATORIO1_DB2_VARIABLERECORDBIN_H
