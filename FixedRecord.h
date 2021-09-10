#ifndef LABORATORIO1_BD2_FIXEDRECORD_H
#define LABORATORIO1_BD2_FIXEDRECORD_H
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

struct Alumno
{
    char codigo [5];
    char nombre [11];
    char apellidos [20];
    char carrera [15];
};

class FixedRecord{
private:
    string nombreArchivo;
public:
    FixedRecord(string nombreArchivo){
        this->nombreArchivo = nombreArchivo;
    }

    vector<Alumno> load(){
        vector<Alumno> alumnos;

        string line;
        ifstream file(nombreArchivo); //Abre el archivo
        if(file.is_open()){ //Verificamos que el archivo este abierto
            while(getline(file,line)){//Leer linea por linea
                cout << line << endl;
            }
            file.close();
        }else{
            cout << "El archivo no esta abierto" << endl;
        }

        return alumnos;
    }

    void add(Alumno record, int pos){
        fstream outFile;
        outFile.open(this->nombreArchivo, ios::out | ios::binary);
        if (outFile.is_open()) {
            outFile.seekg(pos * sizeof(record), ios::beg);
            outFile.write((char *) &record, sizeof(record));
            outFile.close();
        }else cout << "No se pudo abrir el archivo.\n";
    }

    Alumno readRecord(int pos){

    }

};

#endif //LABORATORIO1_BD2_FIXEDRECORD_H
