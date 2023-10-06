//Clase Seguridad

#include<iostream>
#include "Software.h"

using namespace std;

class Seguridad: public Software{
	private:
		string malware;
	public:
		Seguridad():Software(){};
		Seguridad(string name, string dev, int minAge, float price, string malware):Software(name, dev, minAge, price){this->malware = malware;};
		string getMalware(){return this->malware;};
		void setMalware(string malware){this->malware = malware;};
};