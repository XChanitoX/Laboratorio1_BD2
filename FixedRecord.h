#ifndef LABORATORIO1_BD2_FIXEDRECORD_H
#define LABORATORIO1_BD2_FIXEDRECORD_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

struct Alumno {

    char codigo[5];
    char nombre[11];
    char apellidos[20];
    char carrera[15];

    Alumno() {
        for (char & i : codigo)
            i = ' ';
        for (char & i : nombre)
            i = ' ';
        for (char & i : apellidos)
            i = ' ';
        for (char & i : carrera)
            i = ' ';
    }

    void imprimir() {
        std::cout << "Codigo: " << codigo << "\n";
        std::cout << "Nombre: " << nombre << "\n";
        std::cout << "Apellidos: " << apellidos << "\n";
        std::cout << "Carrera: " << carrera << "\n";
        std::cout << "\n";
    }

    void asignarValores(std::string codigo_, std::string nombre_, std::string apellidos_, std::string carrera_){
        strcpy(codigo,codigo_.c_str());
        strcpy(nombre,nombre_.c_str());
        strcpy(apellidos,apellidos_.c_str());
        strcpy(carrera,carrera_.c_str());
        codigo[codigo_.length()]=' ';
        nombre[nombre_.length()]=' ';
        apellidos[apellidos_.length()]=' ';
        carrera[carrera_.length()]='\n';
    }

};

class FixedRecord {

private:
    std::string fileName;

public:
    FixedRecord(const std::string nombreArchivo) {
        this->fileName = nombreArchivo;
    }

    void add(Alumno alumno) {
        std::ofstream file(fileName,std::ios::out);
        if (!file.is_open())
            std::cout << "El archivo no pudo abrirse" << std::endl;
        else{
            file.seekp(std::ios::end);
            file << alumno.codigo << alumno.nombre << alumno.apellidos << alumno.carrera;
        }
        file.close();
        //std::ofstream File;
        //File.open(fileName, std::ios::app);
        //File.write((char *) &alumno, sizeof(alumno));
        //File.close();
    }

    std::vector<Alumno> load() {
        std::vector<Alumno> alumnos;
        std::ifstream File;
        std::string registro;
        File.open(fileName, std::ios::in);
        while (getline(File, registro)) {
            Alumno alumno;
            strncpy(alumno.codigo, registro.substr(0, 4).c_str(), 5);
            strncpy(alumno.nombre, registro.substr(5, 10).c_str(), 11);
            strncpy(alumno.apellidos, registro.substr(16, 19).c_str(), 20);
            strncpy(alumno.carrera, registro.substr(36, 14).c_str(), 15);
            alumnos.push_back(alumno);
        }
        File.close();
        return alumnos;
    }

    Alumno readRecord(const int &pos) {
        std::ifstream File;
        std::string registro;
        File.open(fileName, std::ios::in);

        int physical = pos * (sizeof(Alumno) + 2);
        File.seekg(physical);

        getline(File, registro);
        Alumno alumno;
        strncpy(alumno.codigo, registro.substr(0, 4).c_str(), 5);
        strncpy(alumno.nombre, registro.substr(5, 10).c_str(), 11);
        strncpy(alumno.apellidos, registro.substr(16, 19).c_str(), 20);
        strncpy(alumno.carrera, registro.substr(36, 14).c_str(), 15);

        return alumno;
    }
};

#endif //LABORATORIO1_BD2_FIXEDRECORD_H
