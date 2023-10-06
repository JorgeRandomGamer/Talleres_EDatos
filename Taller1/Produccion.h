//Clase Prouccion

#include<iostream>
#include "Software.h"

using namespace std;

class Produccion: public Software{
	private:
		string tipoSolucion;
	public:
		Produccion():Software(){};
		Produccion(string name, string dev, int minAge, float price, string tipoSolucion):Software(name, dev, minAge, price){this->tipoSolucion = tipoSolucion;};
		string getTipoSolucion(){return this->tipoSolucion;};
		void setTipoSolucion(string tipoSolucion){this->tipoSolucion = tipoSolucion;};
};
