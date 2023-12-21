#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>

using namespace std;

struct Server {
    string id, nombre, tipo;
    vector<pair<Server*, pair<int, int>>> conexiones;
    int distancia;  // Distancia acumulada
    int velocidad;  // Velocidad acumulada
};

const int INF = 1e9;  // Valor grande para representar la distancia infinita

vector<Server*> leerArchivo(string nombreArchivo) {
    // Leer archivos
    vector<Server*> listaGeneral;
    ifstream file(nombreArchivo);
    if (!file) {
        cout << "El archivo '" + nombreArchivo + "' no pudo abrirse" << endl;
        return listaGeneral;
    }
    string linea;

    getline(file, linea);

    while (getline(file, linea)) {
        stringstream ss(linea);
        Server* s = new Server;
        getline(ss, s->id, ',');
        getline(ss, s->nombre, ',');
        getline(ss, s->tipo, ',');

        listaGeneral.push_back(s);
    }
    file.close();
    return listaGeneral;
}

void generarConexiones(vector<Server*>& listaGeneral) {
    ifstream file("conexiones.csv");
    if (!file) {
        cout << "El archivo 'conexiones.csv' no pudo abrirse" << endl;
        return;
    }

    string linea;
    getline(file, linea);

    while (getline(file, linea)) {
        stringstream ss(linea);
        string idClient, idServer, speed, distance;
        getline(ss, idClient, ',');
        getline(ss, idServer, ',');
        getline(ss, speed, ',');
        getline(ss, distance, ',');

        int sp = stoi(speed);
        int dist = stoi(distance);

        for (Server* s : listaGeneral) {
            if (s->id == idClient) {
                for (Server* s2 : listaGeneral) {
                    if (s2->id == idServer) {
                        s->conexiones.push_back(make_pair(s2, make_pair(sp, dist)));
                        if (s2->tipo == "router") {
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
}

void bellmanFord(vector<Server*>& servers, Server* source) {
    for (Server* s : servers) {
        s->distancia = (s == source) ? 0 : INF;
        s->velocidad = 0;
    }

    for (int i = 0; i < servers.size() - 1; ++i) {
        for (Server* s : servers) {
            for (const auto& con : s->conexiones) {
                int altDistancia = s->distancia + con.second.second; // Distancia acumulada
                int altVelocidad = s->velocidad + con.second.first;   // Velocidad acumulada

                if (altDistancia < con.first->distancia || (altDistancia == con.first->distancia && altVelocidad > con.first->velocidad)) {
                    con.first->distancia = altDistancia;
                    con.first->velocidad = altVelocidad;
                }
            }
        }
    }
}

void menu(vector<Server*>& listaGeneral) {
    int option;
    Server* serverActual = listaGeneral[0];
    Server* serverObjetivo;

    do {
        cout << "Servidor Actual: " << serverActual->nombre << endl;
        cout << "\n\tMenu\n";
        cout << "\n1) Ver Servidores y Conexiones" << endl;
        cout << "2) Enviar archivo" << endl;
        cout << "3) Cambiar Servidor" << endl;
        cout << "0) Salir" << endl;
        cout << "\nSeleccione opcion: ";
        cin >> option;

        switch (option) {
            case 1:
                for (Server* s : listaGeneral) {
                    cout << "Id: " << s->id << ", nombre: " << s->nombre << ", Tipo: " << s->tipo << endl;
                    cout << "Conexiones: {";
                    for (const auto& con : s->conexiones) {
                        cout << con.first->nombre << ", Velocidad: " << con.second.first << ", Distancia: " << con.second.second << " ";
                    }
                    cout << "}" << endl;
                }
                break;
            case 2:
                int tamano, idServerObjetivo;
                cout << "Ingrese el tamano del archivo: ";
                cin >> tamano;
                cout << "Ingrese la ID del servidor al cual enviará el archivo: ";
                cin >> idServerObjetivo;
                serverObjetivo = nullptr;
                for (Server* s : listaGeneral) {
                    if (idServerObjetivo == stoi(s->id)) {
                        serverObjetivo = s;
                        break;
                    }
                }
                if (serverObjetivo != nullptr) {
                    bellmanFord(listaGeneral, serverActual);
                    if (serverObjetivo->distancia == INF) {
                        cout << "No hay conexión entre el servidor actual y el servidor objetivo." << endl;
                    } else {
                        cout << "Tiempo estimado de envío: " << serverObjetivo->distancia << " segundos" << endl;
                    }
                } else {
                    cout << "Servidor objetivo no encontrado." << endl;
                }
                break;
            case 3:
                int searchID;
                cout << "Ingrese la ID del servidor al cual cambiar: ";
                cin >> searchID;
                serverActual = nullptr;
                for (Server* s : listaGeneral) {
                    if (searchID == stoi(s->id)) {
                        serverActual = s;
                        break;
                    }
                }
                if (serverActual == nullptr) {
                    cout << "Servidor no encontrado." << endl;
                }
                break;
            case 0:
                break;
            default:
                cout << "Opción no válida. Inténtelo de nuevo." << endl;
        }
    } while (option != 0);
}

int main() {
    vector<Server*> listaGeneral = leerArchivo("servidores.csv");
    generarConexiones(listaGeneral);
    menu(listaGeneral);

    // Liberar memoria al final del programa
    for (Server* s : listaGeneral) {
        delete s;
    }

    return 0;
}
