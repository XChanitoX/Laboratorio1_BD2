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

    void asignarValores(std::string codigo_, std::string nombre_, std::string apellidos_,std::string carrera_){

        //Se asignan los datos del alumno
        strcpy(codigo,codigo_.c_str());
        strcpy(nombre,nombre_.c_str());
        strcpy(apellidos,apellidos_.c_str());
        strcpy(carrera,carrera_.c_str());

        //Se asignan espacios en blanco para que no sea NULL
        codigo[codigo_.length()]=' ';
        nombre[nombre_.length()]=' ';
        apellidos[apellidos_.length()]=' ';
        carrera[carrera_.length()]=' ';
    }

};

class FixedRecord {

private:
    std::string fileName;

public:
    FixedRecord(std::string nombreArchivo) {
        this->fileName = nombreArchivo;
    }

    std::vector<Alumno> load() {
        std::vector<Alumno> alumnos;
        //Accediendo al archivo
        std::ifstream File;
        std::string registro;
        File.open(fileName, std::ios::in);
        //Obtenemos cada uno de los registros del archivo
        while (getline(File, registro)) {
            Alumno alumno = Alumno();
            //Se asigna cada parte del registro a su correspondiente atributo en alumno
            strncpy(alumno.codigo, registro.substr(0, 4).c_str(), 5);
            strncpy(alumno.nombre, registro.substr(5, 10).c_str(), 11);
            strncpy(alumno.apellidos, registro.substr(16, 19).c_str(), 20);
            strncpy(alumno.carrera, registro.substr(36, 14).c_str(), 15);
            //Se añade el alumno al vector
            alumnos.push_back(alumno);
        }
        File.close();
        return alumnos;
    }

    void add(Alumno record) {
        char saltoLinea = '\n';
        //Accedemos al archivo
        std::ofstream outFile;
        outFile.open(fileName, std::ios::app);
        //Escribimos en el archivo un salto de linea
        outFile.write((char*) &saltoLinea, sizeof (saltoLinea));
        //Escribimos el nuevo registro en el archivo
        outFile.write((char*) &record, sizeof (record));
        outFile.close();
    }

    Alumno readRecord(const int &pos) {
        //Accediendo al archivo
        std::ifstream File;
        std::string registro;
        File.open(fileName, std::ios::in);

        //Se calcula la posicion fisica del registro
        int physical = pos * (sizeof(Alumno) + 2);
        //Se apunta a la posicion fisica
        File.seekg(physical);

        //Se obtiene el registro de esa posicion
        getline(File, registro);
        Alumno alumno;
        //Se asigna cada parte del registro a su correspondiente atributo en alumno
        strncpy(alumno.codigo, registro.substr(0, 4).c_str(), 5);
        strncpy(alumno.nombre, registro.substr(5, 10).c_str(), 11);
        strncpy(alumno.apellidos, registro.substr(16, 19).c_str(), 20);
        strncpy(alumno.carrera, registro.substr(36, 14).c_str(), 15);

        return alumno;
    }
};

#endif //LABORATORIO1_BD2_FIXEDRECORD_H
