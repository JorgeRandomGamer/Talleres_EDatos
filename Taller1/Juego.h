//Clase Juego

#include<iostream>
#include "Software.h"


class Game: public Software{
	private:
		string genero;
	public:
		Game():Software(){};
		Game(string name, string dev, int minAge, float price, string genero):Software(name, dev, minAge, price){this->genero = genero;};
		string getGenero(){return this->genero;};
		void setGenero(string genero){this->genero = genero;};
};

