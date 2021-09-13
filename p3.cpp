#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Alumno{
    std::string Nombre;
    std::string Apellidos;
    std::string Carrera;
    float mensualidad = 0.00;

    void imprimir() {
        std::cout << "Nombre: " << Nombre << "\n";
        std::cout << "Apellidos: " << Apellidos << "\n";
        std::cout << "Carrera: " << Carrera << "\n";
        std::cout << "Mensualidad: " << mensualidad << "\n";
        std::cout << "\n";
    }

    void asignarValores(std::string nombre_, std::string apellidos_, std::string carrera_,float mensualidad_){
        //Se asignan los datos del alumno
        Nombre = nombre_;
        Apellidos = apellidos_;
        Carrera = carrera_;
        mensualidad = mensualidad_;
    }

};

class VariableRecord{
private:
    std::string fileName;

public:
    VariableRecord(std::string nombreArchivo){
        this->fileName = nombreArchivo;
    }

    std::vector<Alumno> load(){
        std::vector<Alumno> alumnos;
        int contador = 0;
        //Accediendo al archivo
        std::ifstream File;
        std::string registro;
        File.open(fileName, std::ios::in);
        //Obtenemos cada uno de los registros del archivo
        while (getline(File, registro)) {
            if (contador == 0)
                std::getline(File,registro);
            Alumno alumno = Alumno();
            //Se asigna cada parte del registro a su correspondiente atributo en alumno
            std::string space_delimiter = "|";
            std::vector<std::string> campos{};

            size_t pos = 0;
            while (((pos = registro.find(space_delimiter)) != std::string::npos)) {
                campos.push_back(registro.substr(0, pos));
                registro.erase(0, pos + 1);
            }

            alumno.Nombre = campos[0];
            alumno.Apellidos = campos[1];
            alumno.Carrera = campos[2];
            alumno.mensualidad = std::stof(registro.substr(0,pos));

            //Se añade el alumno al vector
            alumnos.push_back(alumno);
            contador++;
        }
        File.close();
        return alumnos;
    }

    void add(Alumno record){
        std::string registro;
        //Creamos el registro a agregar
        registro = record.Nombre + '|' + record.Apellidos + '|' + record.Carrera + '|' + std::to_string(record.mensualidad) + '\n';
        //Abrimos el archivo
        std::ofstream File;
        File.open(fileName, std::ofstream::app);
        //Agregamos el registro al archivo
        File<<registro;
        File.close();
    }

    Alumno readRecord(int pos){
        pos += 2;
        //Accedemos al archivo
        std::ifstream File;
        File.open(fileName);
        std::string registro;
        //Nos posicionamos en el registro deseado
        while(pos>0){
            std::getline(File,registro);
            pos--;
        }

        Alumno alumno;
        std::string space_delimiter = "|";
        std::vector<std::string> campos{};

        size_t posicion = 0;
        while (((posicion = registro.find(space_delimiter)) != std::string::npos)) {
            campos.push_back(registro.substr(0, posicion));
            registro.erase(0, posicion + 1);
        }

        alumno.Nombre = campos[0];
        alumno.Apellidos = campos[1];
        alumno.Carrera = campos[2];
        alumno.mensualidad = stof(registro.substr(0, posicion));

        File.close();
        return alumno;
    }
};

int main(){
    string fileName = "../archivos/datos2.txt";
    VariableRecord funcionPrincipal = VariableRecord(fileName);

    cout << endl << "-------------------load-----------------" << endl;
    vector<Alumno> alumnos = funcionPrincipal.load();
    cout << "Imprimiendo los registros de los alumnos 1,2,3: " << endl << endl;
    alumnos[0].imprimir();
    alumnos[1].imprimir();
    alumnos[2].imprimir();


    cout << "-------------------add------------------" << endl;
    Alumno alumnoA = Alumno();
    std::string nombre, apellidos, carrera;
    float mensualidad;
    nombre = "Luis";
    apellidos = "Ango Rivera";
    carrera = "Bioingenieria";
    mensualidad = 2200.00;
    alumnoA.asignarValores(nombre, apellidos, carrera, mensualidad);
    funcionPrincipal.add(alumnoA);
    cout << "Alumno agregado con exito." << endl;


    cout << endl << "----------------readRecord--------------" << endl;
    cout << "Tomando como primer elemento el registro en la posicion 0..." << endl;
    cout << "Imprimiendo el registro del alumno en la posicion 1: " << endl;
    Alumno alumnoB;
    alumnoB = funcionPrincipal.readRecord(1);
    alumnoB.imprimir();

    return 0;
}