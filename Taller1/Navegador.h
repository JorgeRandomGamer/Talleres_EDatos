//Clase Navegador

#include<iostream>
#include<vector>
#include "Software.h"

using namespace std;

class Navegador: public Software{
	private:
		vector<string> historial;
	public:
		Navegador():Software(){};
		Navegador(string name, string dev, int minAge, float price):Software(name, dev, minAge, price){};
		string verHistorial(){
            string hist = "";
            for(int i=0;i<10;i++){
                hist += historial[i];
                if(i!= 9){hist += ", ";}
            }
            return hist;
        };
};