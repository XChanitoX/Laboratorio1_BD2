#include <fstream>
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
    std::string _filename;

public:
    VariableRecordBin(std::string  filename);

    std::vector<Matricula> load();

    void add(Matricula record);

    Matricula readRecord(int pos);
};

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
    std::ifstream metafile("metadata." + _filename, std::ios::binary);
    metafile.seekg(pos * sizeof(MetaDataMatricula), std::ios::beg);
    MetaDataMatricula metadata{};
    metafile.read(reinterpret_cast<char *>(&metadata), sizeof(metadata));
    metafile.close();

    std::ifstream file(_filename, std::ios::binary);
    file.seekg(metadata._pos, std::ios::beg);



    return Matricula;
}