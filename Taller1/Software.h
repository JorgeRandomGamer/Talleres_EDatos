//Clase Software

#pragma once
#include<iostream>
#include<vector>
#include "User.h"

using namespace std;

class Software{
	private:
		string name, dev;
		int minAge;
		double price;
		bool log;
		vector<User> listaUsuarios;
	public:
		Software(){};
		Software(string name, string dev, int minAge, double price)
		{
			this->name = name;
			this->dev = dev;
			this->minAge = minAge;
			this->price = price;
		};
		string getName(){return this->name;};		
		string getDev(){return this->dev;};
		double getPrice(){return this->price;};
		int getMinAge(){return this->minAge;};
		void setName(string name){this->name = name;};
		void setDev(string dev){this->dev = dev;};
		void setMinAge(int minAge){this->minAge = minAge;};
		void setPrice(double price){this->price = price;};
		int getCantUsuarios(){return this->listaUsuarios.size();};
		void addUser(User u){this->listaUsuarios.push_back(u);}
		void eliminarUsuario(string nombreUsuario)
		{
			for(int i=0;i<listaUsuarios.size();i++)
			{	
				if(listaUsuarios[i].getName() == nombreUsuario)
				{
					listaUsuarios.erase(listaUsuarios.begin()+i);
				}
			}
		}	
};