#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

/*
El usuario de la plataforma debe entregar el peso del archivo que desea
enviar (lo que afecta a la velocidad de conexión). Por ejemplo, si desde el
cliente con id 0 (ver imagen, línea 2) deseo enviar un archivo de 1200 mb,
entonces el archivo debe ser particionado en 4 partes, debido a que la
conexión solo acepta 300 mb como máximo.
La distancia también afecta el tiempo de conexión, ya que entrega la
información de cuantos segundos se demora en enviar un archivo.
Siguiendo con el ejemplo anterior, si la misma persona desea enviar el
archivo de 1200 mb, entonces debe dividirse en 4 partes, cada parte se
demora 1 segundo en generar la conexión con el router con id 10, por lo
tanto, solo para que el archivo completo llegue al router, se demorara un
tiempo total de 4 segundos.
Usuario además tiene que ser capaz de conocer la ruta que esta tomando el
archivo y conocer los tiempos entre cada nodo que se comunica.
*/
struct Server{
    string id,name, type;
    vector<Server> connections;
};

vector<Server> readCsv(string nameScv){
    vector<Server> serverList;
    ifstream file(nameScv);
    if(!file){
        cout<<"the file "+nameScv+" hasn't opened"<<endl;
        return serverList;
    }
    string line; 

    getline(file, line);
    while(getline(file, line)){

        stringstream ss(line);
        Server s;

        getline(ss, s.id, ',');
        getline(ss, s.name, ',');
        getline(ss, s.type, ',');

        serverList.push_back(s);
    }
    file.close();
    return serverList;
};

void generateConnections(vector<Server> list){
    ifstream file("conexiones.csv");
    if(!file){
        cout<<"the file 'conexiones.csv' hasn't opened"<<endl;
        return;
    }
    string line; 
    getline(file, line);
    while(getline(file, line)){

        stringstream ss(line);
        string idClient, idServer, speed, distance;
        getline(ss, idClient, ',');
        getline(ss, idServer, ',');
        getline(ss, speed, ',');
        getline(ss, distance, ',');
        
        for(Server s : list){
            cout<<s.name<<endl;
            if(s.id == idClient){
                for(Server s2 : list){
                    cout<<s2.name<<endl;
                    if(s2.id == idServer){
                        s.connections.push_back(s2);
                    }
                }
            }
        }
    }
    file.close();
}


void menu(vector<Server> list){
    int option;
    do{
        cout<<"\n\tMenu\n";
        cout<<"\n1) View Servers"<<endl;
        cout<<"2) Send files"<<endl;
        cout<<"0) Close app"<<endl;
        cout<<"\nInsert option: ";cin>>option;
        
        switch (option){
        case 1: 
            for(Server s : list){
                cout<<"Id: "<<s.id<<", Nane: "<<s.name<<endl;
            }
            break;
        case 2: generateConnections(list);
        case 0: break;
        }
    }while(option != 0);
};


int main(){
    
    vector<Server> serverList = readCsv("servidores.csv");
    generateConnections(serverList);
    menu(serverList);
    for(Server s : serverList){
        for(Server s2 : s.connections){
            cout<<s.name<<"->"<<s2.name<<endl;
        }
    }

    return 0;
}