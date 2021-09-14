//
// Created by ceduardosq on 9/13/21.
//

#include <fstream>
#include "VariableRecordBin.h"

VariableRecordBin::VariableRecordBin(std::string filename) : _filename(std::move(filename)) {
    size_t indexDot = _filename.find_last_of(".");
    _metafilename = _filename.substr(0, indexDot) + ".meta.bin";

    std::ofstream metafile(_metafilename, std::ios::binary);
    metafile.close();

    std::ofstream file(_filename, std::ios::binary);
    file.close();
}

std::vector<Matricula> VariableRecordBin::load() {
    std::ifstream metafile(_metafilename, std::ios::binary | std::ios::ate);
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

    std::ofstream metafile(_metafilename, std::ios::binary | std::ios::app);
    MetaDataMatricula metaDataMatricula = {pos, (int)sizeof(record)};
    metafile.write(reinterpret_cast<char *> (&metaDataMatricula), sizeof(metaDataMatricula));
    metafile.close();
}

Matricula VariableRecordBin::readRecord(int pos) {
    std::ifstream metafile(_metafilename, std::ios::binary);
    metafile.seekg(pos * sizeof(MetaDataMatricula), std::ios::beg);
    MetaDataMatricula metadata{};
    metafile.read(reinterpret_cast<char *>(&metadata), sizeof(metadata));
    metafile.close();

    std::ifstream file(_filename, std::ios::binary);
    file.seekg(metadata._pos, std::ios::beg);
    Matricula matricula{};
    file.read(reinterpret_cast<char *>(&matricula), metadata._size);
    file.close();

    return matricula;
}
