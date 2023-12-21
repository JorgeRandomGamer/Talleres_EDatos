#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>

using namespace std;

/*
El usuario de la plataforma debe entregar el peso del archivo que desea enviar.
Por ejemplo, si desde el cliente con id 0 deseo enviar un archivo de 1200 mb, 
entonces el archivo debe ser particionado en 4 partes, debido a que la conexión 
solo acepta 300 mb como máximo.

La distancia también afecta el tiempo de conexión, ya que entrega la
información de cuantos segundos se demora en enviar un archivo.

Si la misma persona desea enviar el archivo de 1200 mb, entonces debe dividirse 
en 4 partes, cada parte se demora 1 segundo en generar la conexión con el router
con id 10, por lo tanto, solo para que el archivo completo llegue al router, se 
demorara un tiempo total de 4 segundos.

Usuario además tiene que ser capaz de conocer la ruta que esta tomando el
archivo y conocer los tiempos entre cada nodo que se comunica.
*/

//Arreglar print
//Controlar ciclo infinito
//Dividir en partes

struct Server{
    //Estructura del server
    string id,nombre,tipo;
    vector<pair<Server*,pair<int,int>>> conexiones;
    int distancia, velocidad;
};

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
        
        int sp = stoi(speed);
        int dist = stoi(distance);

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

void bellmanFord(vector<Server*> lista, Server* origen) {
    for (Server* s : lista) {
        s->distancia = numeric_limits<int>::max();
        s->velocidad = 0;
    }

    origen->distancia = 0;
    origen->velocidad = 0;

    for (int i = 0; i < lista.size() - 1; i++) {
        for (Server* s : lista) {
            for (pair<Server*, pair<int,int>> con : s->conexiones) {
                int altDistancia = s->distancia + con.second.second; // Distancia acumulada
                int altVelocidad = s->velocidad + con.second.first;   // Velocidad acumulada

                if (altDistancia < con.first->distancia || (altDistancia == con.first->distancia && altVelocidad > con.first->velocidad)) {
                    con.first->distancia = altDistancia;
                    con.first->velocidad = altVelocidad;
                }
            }
        }
    }
};


void enviarMensaje(Server* server, Server* objetivo){
    for(pair<Server*, pair<int,int>> con : server->conexiones){
        if(con.first->tipo == "router"){
            cout<<con.first->nombre<<endl;
            for(pair<Server*, pair<int,int>> con2 : objetivo->conexiones){
                if(con2.first->id == con.first->id){
                    cout<<"Mensaje enviado a traves de "<<con.first->nombre<<endl;
                    
                }
            }
        }
    }
};

void menu(vector<Server*> listaGeneral){
    //Menu
    int opcion;
    Server* serverActual = listaGeneral[0];
    Server* serverObjetivo;

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
                for (pair<Server*, pair<int,int>> con : s->conexiones) {
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
                bellmanFord(listaGeneral, serverActual);
                cout << "Tiempo de envio: " << serverObjetivo->distancia << " segundos" << endl;
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