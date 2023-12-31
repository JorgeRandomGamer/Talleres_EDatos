#include <iostream>
#include <vector>
#include <climits>
#include <fstream>

using namespace std;

const int filas = 6;
const int columnas = 7;
int player = 1;

class Connect4{
    private:
    int tablero[filas][columnas];
    int dificultad = 2;

    public:
    Connect4(){ //Inicializa un tablero vacio
        for(int i = 0; i < filas; i++){
            for(int j = 0; j < columnas; j++){
                tablero[i][j] = 0;
            }
        }
    }

    void setDificultad(int dif){ //Setea la dificultad de la partida
        dificultad = 2*dif-1;
    }

    void mostrarTablero(){ //Muestra el tablero por pantalla segun el estado de la partida
        for(int i = 0; i < filas; i++){
            for(int j = 0; j < columnas; j++){
                switch(tablero[i][j]){
                    case 0:
                        cout<<"[]";break;
                    case 1: 
                        cout<<"X ";break;
                    case 2:
                        cout<<"O ";break; 
                }
            }
            cout<<endl;
        }
        cout<<endl;
    }

    bool columnaLlena(int b){ //Verifica si la columna está llena, devuelve true si lo está
        for(int i=0; i<filas;i++){
            if(tablero[i][b] == 0){return false;}
        }
        return true;
    }

    bool ingresarFicha(int b, int jugador){//Ingresa la ficha a la columna ingresada
        if(b < 0 || b >= columnas || columnaLlena(b)){
            return false;
        }

        for(int fila = filas - 1; fila >= 0; fila--){
            if(tablero[fila][b] == 0){
                tablero[fila][b] = jugador;
                return true;
            }
        }
        return false;
    }

    bool ganador(int player){ //Comprueba la victoria del jugador
       // Verificar victoria en horizontal
        for(int a = 0; a < filas; a++){
            for(int b = 0; b <= columnas-4; b++){
                bool conectadas = true;
                for(int i = 0; i < 4; i++){
                    if(tablero[a][b + i] != player){
                        conectadas = false;
                        break;
                    }
                }
                if(conectadas){
                    return true;
                }
            }
        }

        // Verificar victoria en vertical
        for(int b = 0; b < columnas; b++){
            for (int a = 0; a <= filas - 4; a++){
                bool conectadas = true;
                for(int i = 0; i < 4; i++){
                    if(tablero[a + i][b] != player){
                        conectadas = false;
                        break;
                    }
                }
                if (conectadas) {
                    return true;
                }
            }
        }

        // Verificar victoria en diagonal
        for(int a = 3; a < filas; a++){
            for(int b = 0; b <= columnas - 4; b++){
                bool conectadas = true;
                for(int i = 0; i < 4; i++){
                    if(tablero[a - i][b + i] != player){
                        conectadas = false;
                        break;
                    }
                }
                if(conectadas){
                    return true;
                }
            }
        }

        // 4 en diagonal
        for(int a = 0; a <= filas - 4; a++){
            for(int b = 0; b <= columnas - 4; b++){
                bool conectadas = true;
                for(int i = 0; i < 4; i++){
                    if(tablero[a + i][b + i] != player){
                        conectadas = false;
                        break;
                    }
                }
                if(conectadas){
                    return true;
                }
            }
        }
        return false;
    }

    int calcularPuntaje(int jugador){//Calcula el puntaje de la profundidad de los movimientos
        int puntaje = 0;
        for (int i = 0; i < filas; i++){
            for(int j = 0; j < columnas; j++){
                if(tablero[i][j] == jugador){
                    puntaje++;
                }
            }
        }
        return puntaje;
    }


    int minimax(int jugadorActual, int profundidad, int alfa, int beta){
        // si llega a la maxima profundidad o algun jugador gana, devuelve el puntaje
        if(profundidad == 0 || ganador(1) || ganador(2)) {
            return calcularPuntaje(jugadorActual);
        }
        
        // inicializamos el mejor puntaje según el jugador actual.
        int mejorPuntaje;
        if(jugadorActual == 1){mejorPuntaje = INT_MIN;}
        else{mejorPuntaje = INT_MAX;}

        // se revisa cada movimiento en el tablero y si la casilla esta vacia se realiza, luego se evalua el puntaje
        for(int b = 0; b < columnas; b++){
            for(int fila = filas - 1; fila >= 0; fila--){
                if(tablero[fila][b] == 0){
                    tablero[fila][b] = jugadorActual;

                    int puntaje = minimax(3 - jugadorActual, profundidad - 1, alfa, beta);

                    if(jugadorActual == 1){
                        mejorPuntaje = max(mejorPuntaje, puntaje);
                        alfa = max(alfa, mejorPuntaje);
                    }else{
                        mejorPuntaje = min(mejorPuntaje, puntaje);
                        beta = min(beta, mejorPuntaje);
                    }

                    tablero[fila][b] = 0;

                    // Podamos el árbol si beta es menor o igual a alfa.
                    if (beta <= alfa) {
                        break;
                    }
                }
            }
        }
        return mejorPuntaje;
    }

    void jugar(){//Turno de la maquina
        int mejorPuntaje = INT_MIN;
        int mejorColumna = 0;
    
        for(int b = 0; b < columnas; b++){
            if(!columnaLlena(b)){
                for(int fila = filas - 1; fila >= 0; fila--){
                    if(tablero[fila][b] == 0){
                        tablero[fila][b] = 2;
                        
                        int puntaje = minimax(1, dificultad, INT_MIN, INT_MAX);
                        tablero[fila][b] = 0;
    
                        if(puntaje > mejorPuntaje){
                            mejorPuntaje = puntaje;
                            mejorColumna = b;
                        }
                        break;
                    }
                }
            }
        }
        for(int fila = filas - 1; fila >= 0; fila--){
            if(tablero[fila][mejorColumna] == 0){
                tablero[fila][mejorColumna] = 2;
                break;
            }
        }
    }

    void guardarPartida(string nombreArchivo){//Guarda la partida en un archivo
        ofstream archivo(nombreArchivo);

        for(int i = 0; i < filas; i++){
            for(int j = 0; j < columnas; j++){
                archivo << tablero[i][j];

                if(j < columnas - 1){
                    archivo<<",";
                }
            }
            archivo<<endl;
        }
        archivo<<endl;
        archivo.close();
    }

    void cargarPartida(string nombreArchivo){//Carga la partida desde un archivo
        ifstream archivo(nombreArchivo);

        for(int i = 0; i < filas; i++){
            for(int j = 0; j < columnas; j++){
                char valor;
                archivo>>valor;
                tablero[i][j] = valor - '0';
                archivo.ignore();
            }
        }
        archivo.close();
    }
};

int main(){
    Connect4 juego;
    juego.cargarPartida("ultima_partida.csv");  
    int dificultad = 0;
    bool guardado = false;
    cout<<"\tConnect4\n";
    while(dificultad < 1 || dificultad > 3){
        cout<<"Seleccione dificultad: \n1)Facil\n2)Medio\n3)Dificil\n";cin>>dificultad;
    }
    juego.setDificultad(dificultad);

    for(int i = 0; i < filas * columnas; i++){
        
        int jugadorActual;
        if(i % 2 == 0){jugadorActual = 1;}
        else{jugadorActual = 2;}
        
        cout<<"Turno del Jugador "<<jugadorActual<<endl;
        juego.mostrarTablero();

        if(jugadorActual == 1){
            int b;
            cout<<"Seleccione columna (1-7): "<<"0 para guardar partida y cerrar"<<endl;cin>>b;

            if(b == 0){
            juego.guardarPartida("ultima_partida.csv");
            guardado = true;
            break;
            }

            while (!juego.ingresarFicha(b-1, jugadorActual)) {
                cout<<"Movimiento invalido. Ingrese la columna nuevamente: ";cin>>b;
            }
        }else{juego.jugar();}

        if(juego.ganador(jugadorActual)){
            cout<<"El Jugador "<<jugadorActual<<" gana"<<endl;
            juego.mostrarTablero();
            break;
        }
    }
    if(!juego.ganador(1) && !juego.ganador(2) && !guardado){
        cout<<"EMPATE"<<endl;
    }
    if(!guardado){
        juego.guardarPartida("Partidas.csv");
        Connect4 fin;
        fin.guardarPartida("ultima_partida.csv");
    }
    return 0;
}