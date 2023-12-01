#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int filas = 6;
const int columnas = 7;
int player = 1;

class Connect4 {
    private:
    int tablero[filas][columnas];
    int dificultad = 2;

    public:
    Connect4(){
        for(int i = 0; i < filas; i++){
            for(int j = 0; j < columnas; j++){
                tablero[i][j] = 0;
            }
        }
    }

    void setDificultad(int dif){
        dificultad = dif;
    }

    void mostrarTablero(){
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

    bool columnaLlena(int col) {
        for(int i=0; i<filas;i++){
            if(tablero[i][col] == 0){return false;}
        }
        return true;
    }

    bool hacerMovimiento(int col, int jugador){
        if(col < 0 || col >= columnas || columnaLlena(col)){
            return false;
        }

        for(int fila = filas - 1; fila >= 0; fila--){
            if (tablero[fila][col] == 0) {
                tablero[fila][col] = jugador;
                return true;
            }
        }
        return false;
    }

    bool ganador(int player) {
       // Verificar victoria en horizontal
        for (int row = 0; row < filas; ++row) {
            for (int col = 0; col <= columnas - 4; ++col) {
                bool win = true;
                for (int i = 0; i < 4; ++i) {
                    if (tablero[row][col + i] != player) {
                        win = false;
                        break;
                    }
                }
                if (win) {
                    return true;
                }
            }
        }

        // 4 en vertical
        for (int col = 0; col < columnas; ++col) {
            for (int row = 0; row <= filas - 4; ++row) {
                bool win = true;
                for (int i = 0; i < 4; ++i) {
                    if (tablero[row + i][col] != player) {
                        win = false;
                        break;
                    }
                }
                if (win) {
                    return true;
                }
            }
        }

        // 4 en horizontal
        for (int row = 4 - 1; row < filas; ++row) {
            for (int col = 0; col <= columnas - 4; ++col) {
                bool win = true;
                for (int i = 0; i < 4; ++i) {
                    if (tablero[row - i][col + i] != player) {
                        win = false;
                        break;
                    }
                }
                if (win) {
                    return true;
                }
            }
        }

        // 4 en diagonal
        for (int row = 0; row <= filas - 4; ++row) {
            for (int col = 0; col <= columnas - 4; ++col) {
                bool win = true;
                for (int i = 0; i < 4; ++i) {
                    if (tablero[row + i][col + i] != player) {
                        win = false;
                        break;
                    }
                }
                if (win) {
                    return true;
                }
            }
        }
        return false;
    }

    int calcularPuntaje() {
        int puntaje = 0;
        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; ++j) {
                if (tablero[i][j] == 1) {
                    puntaje++;
                }
            }
        }
        return puntaje;
    }


    int minimax(int jugadorActual, int profundidad, int alfa, int beta){
        // si llega a la maxima profundidad o algun jugador gana, devuelve el puntaje
        if(profundidad == 0 || ganador(1) || ganador(2)) {
            return calcularPuntaje();
        }
        
        // inicializamos el mejor puntaje según el jugador actual.
        int mejorPuntaje;
        if(jugadorActual == 1){mejorPuntaje = INT_MIN;}
        else{mejorPuntaje = INT_MAX;}

        // se revisa cada movimiento en el tablero y si la casilla esta vacia se realiza, luego se evalua el puntaje
        for(int col = 0; col < columnas; col++){
            for(int fila = filas - 1; fila >= 0; fila--){
                if(tablero[fila][col] == 0){
                    tablero[fila][col] = jugadorActual;

                    int puntaje = minimax(3 - jugadorActual, profundidad - 1, alfa, beta);

                    if(jugadorActual == 1){
                        mejorPuntaje = max(mejorPuntaje, puntaje);
                        alfa = max(alfa, mejorPuntaje);
                    }else{
                        mejorPuntaje = min(mejorPuntaje, puntaje);
                        beta = min(beta, mejorPuntaje);
                    }

                    tablero[fila][col] = 0;

                    // Podamos el árbol si beta es menor o igual a alfa.
                    if (beta <= alfa) {
                        break;
                    }
                }
            }
        }
        return mejorPuntaje;
    }

    void jugar() {
        int mejorPuntaje = INT_MIN;
        int mejorColumna = 0;
    
        for(int col = 0; col < columnas; col++){
            if(!columnaLlena(col)){
                for(int fila = filas - 1; fila >= 0; fila--){
                    if(tablero[fila][col] == 0){
                        tablero[fila][col] = 2;
                        
                        int puntaje = minimax(1, dificultad, INT_MIN, INT_MAX);
                        tablero[fila][col] = 0;
    
                        if(puntaje > mejorPuntaje){
                            mejorPuntaje = puntaje;
                            mejorColumna = col;
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
};

int main(){
    Connect4 juego;
    int dificultad;
    cout<<"\tConnect4\n";
    cout<<"Seleccione dificultad: \n1)Facil\n2)Medio\n3)Dificil\n";cin>>dificultad;
    juego.setDificultad(dificultad);

    for(int i = 0; i < filas * columnas; i++){
        
        int jugadorActual;
        if(i % 2 == 0){jugadorActual = 1;}
        else{jugadorActual = 2;}
        
        cout<<"Turno del Jugador "<<jugadorActual<<endl;
        juego.mostrarTablero();

        if(jugadorActual == 1){
            int col;
            cout<<"Seleccione columna (1-7): ";cin>>col;

            while (!juego.hacerMovimiento(col-1, jugadorActual)) {
                cout<<"Movimiento invalido. Ingrese la columna nuevamente: ";cin>>col;
            }
        }else{juego.jugar();}

        if(juego.ganador(jugadorActual)){
            cout<<"El Jugador "<<jugadorActual<<" gana"<<endl;
            juego.mostrarTablero();
            break;
        }
    }
    if(!juego.ganador(1) && !juego.ganador(2)){
        cout<<"EMPATE"<<endl;
    }
    return 0;
}