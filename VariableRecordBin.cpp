//
// Created by ceduardosq on 9/13/21.
//

#include <fstream>
#include "VariableRecordBin.h"

VariableRecordBin::VariableRecordBin(std::string filename) : _filename(std::move(filename)) {
    std::ofstream file("metadata." + _filename, std::ios::binary);
    file.close();
}

std::vector<Matricula> VariableRecordBin::load() {
    std::ifstream metafile("metadata." + _filename, std::ios::binary | std::ios::ate);
    int size = metafile.tellg(), nRecords = size / sizeof(MetaDataMatricula);
    metafile.seekg(0, std::ios::beg);
    std::vector<MetaDataMatricula> metaRecord(nRecords);
    for (int i = 0; i < nRecords; ++i)
        metafile.read(reinterpret_cast<char *>(&metaRecord[i]), sizeof(MetaDataMatricula));
    metafile.close();

    std::ifstream file(_filename, std::ios::binary);
    std::vector<Matricula> result(nRecords);
    for (int i = 0; i < nRecords; ++i) {
        file.seekg(metaRecord[i]._pos, std::ios::beg);
        file.read(reinterpret_cast<char *>(&result[i]), metaRecord[i]._size);
    }
    file.close();

    return result;
}

void VariableRecordBin::add(Matricula record) {
    std::ofstream file(_filename, std::ios::binary | std::ios::app | std::ios::ate);
    int pos = file.tellp();
    file.write(reinterpret_cast<char *>(&record), sizeof(record));
    file.close();

    std::ofstream metafile("metadata." + _filename, std::ios::binary | std::ios::app);
    MetaDataMatricula metaDataMatricula = {pos, sizeof(record)};
    metafile.write(reinterpret_cast<char *> (&metaDataMatricula), sizeof(metaDataMatricula));
    metafile.close();
}

Matricula VariableRecordBin::readRecord(int pos) {
    return Matricula();
}
