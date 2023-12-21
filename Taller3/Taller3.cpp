#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include <stack>

using namespace std;

struct Server{
    //Estructura del server
    string id,nombre,tipo;
    vector<pair<Server*,pair<double,double>>> conexiones;
    double distancia, velocidad;
};

const int distanciaMax = 10000000;

vector<Server*> leerArchivo(string nombreArchivo){
    //Leer archivos
    vector<Server*> listaGeneral;
    ifstream file(nombreArchivo);
    if(!file){
        cout << "El archivo '" + nombreArchivo + "' no pudo abrirse" <<endl;
        return listaGeneral;
    }
    string linea; 
    getline(file, linea);

    while (getline(file, linea)) {
        stringstream ss(linea);
        Server *s = new Server;
        getline(ss, s->id, ',');
        getline(ss, s->nombre, ',');
        getline(ss, s->tipo, ',');

        listaGeneral.push_back(s);
    }
    file.close();
    return listaGeneral;
};

void generarConexiones(vector<Server*> listaGeneral) {
    //Generar conexiones 
    ifstream file("conexiones.csv");
    if(!file){
        cout << "El archivo 'conexiones.csv' no pudo abrirse" << endl;
        return;
    }
    
    string linea; 
    getline(file, linea);
    
    while(getline(file, linea)){
        stringstream ss(linea);
        string idClient, idServer, speed, distance;
        getline(ss, idClient, ',');
        getline(ss, idServer, ',');
        getline(ss, speed, ',');
        getline(ss, distance, ',');
        
        double sp = stod(speed);
        double dist = stod(distance);

        for (Server* s : listaGeneral) {
            if (s->id == idClient) {
                for (Server* s2 : listaGeneral) {
                    if (s2->id == idServer) {
                        s->conexiones.push_back(make_pair(s2,make_pair(sp, dist)));
                        if(s2->tipo == "router"){
                            s2->conexiones.push_back(make_pair(s, make_pair(sp, dist)));
                        }
                        break;
                    }
                }
                break;
            }
        }
    }
    file.close();
};

void bellmanFord(vector<Server*> lista, Server* origen,Server* objetivo, stack<Server*> camino) {
    for (Server* s : lista) {
        if(s == origen){
            s->distancia = 0;
        }else{
            s->distancia = distanciaMax;
        }
        s->velocidad = 0;
    }

    for (int i = 0; i < lista.size() - 1; i++) {
        for (Server* s : lista) {
            for (pair<Server*, pair<double,double>> con : s->conexiones) {
                // Calcular nuevas distancias y velocidades acumuladas
                double distanciaAcumulada = s->distancia + con.second.second; // Distancia acumulada
                double velocidadAcumulada = s->velocidad + con.second.first;   // Velocidad acumulada

                // Actualizar si se encuentra una ruta más corta
                if (distanciaAcumulada < con.first->distancia || (distanciaAcumulada == con.first->distancia && velocidadAcumulada > con.first->velocidad)) {
                    con.first->distancia = distanciaAcumulada;
                    con.first->velocidad = velocidadAcumulada;
                }
            }
        }
    }

    Server* actual = objetivo;

    while (actual != origen) {
        for (pair<Server*, pair<double,double>> con : actual->conexiones) {
            if (con.first->distancia + con.second.second == actual->distancia && con.first->velocidad + con.second.first == actual->velocidad) {
                camino.push(actual);
                actual = con.first;
            }
        }
    }
    camino.push(actual);

    while(!camino.empty()){
        cout<<camino.top()->nombre<<", ";
        camino.pop();
    }
    cout<<endl;
};

void menu(vector<Server*> listaGeneral){
    //Menu
    int opcion;
    Server* serverActual = listaGeneral[0];
    Server* serverObjetivo;
    stack<Server*> camino;
    stack<Server*> aux;


    do{
        cout << "Servidor Actual: " << serverActual->nombre <<endl;
        cout << "\n\tMenu\n";
        cout << "\n1) Ver Servidores" << endl;
        cout << "2) Enviar archivo" << endl;
        cout << "3) Cambiar Servidor" << endl;
        cout << "0) Salir" << endl;
        cout << "\nSeleccione opcion: ";
        cin >> opcion;
        
        switch (opcion){
        case 1: 
            //Opcion ver los servers
            for (Server* s : listaGeneral) {
                cout << "Id: " << s->id << ", Nombre: " << s->nombre << ", Tipo: "<<s->tipo << endl;
                cout << "Conexiones: {";
                for (pair<Server*, pair<double,double>> con : s->conexiones) {
                    cout << con.first->nombre << ", Velocidad: " << con.second.first << ", Distancia: " << con.second.second << " ";
                }
                cout << "}" << endl;
            }
            break;
        case 2: 
            //Enviar archivos
            int tamano, idServerObjetivo;
            cout << "Ingrese el tamano del archivo: ";
            cin >> tamano;
            cout << "Ingrese la ID del destino: ";
            cin >> idServerObjetivo;
            serverObjetivo = nullptr;
            for (Server* s : listaGeneral) {
                if (idServerObjetivo == stoi(s->id)) {
                    serverObjetivo = s;
                    break;
                }
            }
            if (serverObjetivo != nullptr) {
                bellmanFord(listaGeneral, serverActual, serverObjetivo, camino);
                if (serverObjetivo->distancia == distanciaMax) {
                    cout << "No hay conexion entre el servidor actual y el servidor objetivo." << endl;
                } else {
                    cout << "Tiempo estimado de envio: " << (tamano/serverObjetivo->velocidad)*serverObjetivo->distancia << " segundos" << endl;
                }            
            } else {
                cout << "Destinatrio no encontrado." << endl;
            }
            break;
        case 3: 
            //Cambiar servidor
            int idBuscada;
            cout << "Ingrese la ID del servidor al cual cambiar: ";
            cin >> idBuscada;
            serverActual = nullptr;
            for(Server* s : listaGeneral){
                if(idBuscada == stoi(s->id)){
                    serverActual = s;
                    break;
                }
            }
            if (serverActual == nullptr) {
                cout << "Servidor no encontrado." << endl;
            }
            break;
        case 0: break; //salir
        default: cout << "Opción no válida. Inténtelo de nuevo." << endl;
        }
    }while(opcion != 0);
};


//Main
int main(){
    vector<Server*> listaGeneral = leerArchivo("servidores.csv");
    generarConexiones(listaGeneral);
    menu(listaGeneral);   

    return 0;
}