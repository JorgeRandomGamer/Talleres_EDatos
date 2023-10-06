//Clase Usuario

#pragma once
#include<iostream>
#include<vector>

using namespace std;

class User{
	
	private:
		string name, password, mail, category;
		int age;
		int cant;
		vector<string> softwares;

	public:
		User(){};
		User(string name, int age, string mail, string password, string category){
			this->name = name;
			this->age = age;
			this->mail = mail;
			this->password = password;
			this->category = category;
			this->cant = 0;
			this->softwares = {};
		};

		string getName(){return this->name;};
		int getAge(){return this->age;};
		string getMail(){return this->mail;};
		string getPassword(){return this->password;};
		string getCategory(){return this->category;};
		void setName(string name){this->name = name;};
		void setAge(int	age){this->age = age;};
		void changePassword(string newPass){this->password = newPass;};
		void changeMail(string newMail){this->mail = newMail;};
		int getCant(){return this->cant;};

		string getSoftwares() // obtiene un string con los nombres de los software
		{
			string softwares = "";
			for(int i=0;i<this->cant;i++){
				softwares += this->softwares[i];
				if(i != (this->cant-1)){softwares += ", ";}
			}
			return softwares;
		};

		int buscarSoftware(string nameSoft) //Busca un nombre de software y retorna su posicion
		{
			int pos;
			for(int i=0;i<this->cant;i++)
			{
				if(softwares[i].compare(nameSoft) == 0)
				{
					pos = i;
				}
			}
			return pos;
		}

		void agregarSoftware(string nameSoft) //añade un software mientras no exista antes
		{
			if(softwares.empty() || buscarSoftware(nameSoft) == cant-1){
				this->softwares.push_back(nameSoft);
				this->cant++;
			}
		};

		void borrarSoftware(string nameSoft) // elimina un software
		{
			string aux;
			int pos = buscarSoftware(nameSoft);
			aux = softwares[cant];
			softwares[cant] = softwares[pos];
			softwares[pos] = aux;
			softwares.pop_back();
		};
};
