#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include <queue>

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
};

vector<Server*> leerArchivo(string nombreArchivo){
    //Leer archivos
    
    vector<Server*> listaGeneral;
    ifstream file(nombreArchivo);
    if(!file){
        cout<<"El archivo '"+nombreArchivo+"' no pudo abrirse"<<endl;
        return listaGeneral;
    }
    string linea; 

    getline(file, linea);

    while(getline(file, linea)){

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

vector<Server*> generarConexiones(vector<Server*> listaGeneral){
    //Generar conexiones 
    listaGeneral = leerArchivo("servidores.csv");
    ifstream file("conexiones.csv");
    if(!file){
        cout<<"El archivo 'conexiones.csv' no pudo abrirse"<<endl;
        return listaGeneral;
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
                        s->conexiones.push_back(make_pair(s2, make_pair(sp, dist)));
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
    return listaGeneral;
};

int encontrarCamino(Server* origen, Server* objetivo, int distancia){
    //Funcion para calcular distancias entre servidores
    if(origen == objetivo){
        return distancia;
    }else{
        if (objetivo->tipo == "router") {
            for(pair<Server*, pair<int,int>> con : origen->conexiones){
                if(con.first->id == objetivo->id){
                    distancia += con.second.second/con.second.first;
                    break;
                }
            }
        } else {
            for(pair<Server*, pair<int,int>> con : origen->conexiones){
                if(con.first->tipo == "router"){
                    encontrarCamino(con.first, objetivo, con.second.second/con.second.first);
                }
            }
        }
        return distancia;
    }
};

vector<pair<Server*, pair<Server*,int>>> bellmanFord(vector<Server*> servers, Server* origen){
    //Algoritmo bellmanFord

    vector<pair<Server*, pair<Server*,int>>> distancias;

    cout<< origen->nombre << endl;
    for(Server* s : servers){
        if(s->id == origen->id){
            distancias.push_back(make_pair(origen, make_pair(origen, 0)));
        }else{  
            int dist = encontrarCamino(origen, s, 0);
            distancias.push_back(make_pair(s, make_pair(origen, dist)));
        }
    }
    return distancias;
};

Server* cambiarServidor(int id, Server* server, vector<Server*> listaGeneral){
    //Funcion para buscar servers
    for(Server* s : listaGeneral){
        if(id == stoi(s->id)){
            server = s;
            break;
        }
    }
    return server;
};

void menu(vector<Server*> listaGeneral){
    //Menu
    int option;
    Server* serverActual = listaGeneral[0];
    vector<pair<Server*, pair<Server*,int>>> distancias;

    do{
        cout<<"Servidor Actual: "<<serverActual->nombre<<endl;
        cout<<"\n\tMenu\n";
        cout<<"\n1) Ver Servidores"<<endl;
        cout<<"2) Enviar archivo"<<endl;
        cout<<"3) Cambiar Servidor"<<endl;
        cout<<"0) Salir"<<endl;
        cout<<"\nSeleccione opcion: ";cin>>option;
        
        switch (option){
        case 1: 
            //Opcion ver los servers
            for(Server* s : listaGeneral){
                cout<<"Id: "<<s->id<<", nombre: "<<s->nombre<<", Type: "<<s->tipo<<endl;
                cout<<"Connections: {";
                for(pair<Server*, pair<int,int>> con : s->conexiones){
                    cout<<" - "<<con.first->nombre<<", Speed: "<<con.second.first<<", Distance: "<<con.second.second;
                }
                cout<<"}"<<endl;
            }
            break;
        case 2: 
            //Enviar archivos
            int tamano;
            int idServerObjetivo;
            cout<<"Ingrese el tamano del archivo: ";cin>>tamano;
            cout<<"Ingrese la ID del server al cual enviara el arhivo: ";cin>>idServerObjetivo;
            break;
        case 3: 
            //Cambiar servidor
            int searchID;
            cout<<"Ingress server ID: ";cin>>searchID;
            serverActual = cambiarServidor(searchID, serverActual, listaGeneral);
            distancias = bellmanFord(listaGeneral, serverActual);
            
            break;
            //salir
        case 0: break;
        }
    }while(option != 0);
};


//Main
int main(){
    vector<Server*> listaGeneral;
    listaGeneral = generarConexiones(listaGeneral);
    menu(listaGeneral);   

    return 0;
}