//Clase Ofimatica

#include<iostream>
#include "Software.h"

using namespace std;

class Ofimatica: public Software{
	private:
		int cantArch;
	public:
		Ofimatica():Software(){};
		Ofimatica(string name, string dev, int minAge, float price, int cantArch):Software(name, dev, minAge, price){this->cantArch = cantArch;};
		int getCantArch(){return this->cantArch;};
		void agregarArchivo(){
			this->cantArch += 1;
		}
		void eliminarArchivo(){
			this->cantArch -= 1;
		}

};