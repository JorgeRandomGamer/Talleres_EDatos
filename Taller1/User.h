//Clase Usuario

#pragma once
#include<iostream>
#include<vector>

using namespace std;

class User{
	
	private:
		string name, password, mail, category;
		int age, cantSoft, cantAmigos;
		vector<string> softwares;
		vector<User> amigos;

	public:
		User(){};
		User(string name, int age, string mail, string password, string category){
			this->name = name;
			this->age = age;
			this->mail = mail;
			this->password = password;
			this->category = category;
			this->cantSoft = 0;	
			this->cantAmigos = 0;	
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
		int getCantSoft(){return this->cantSoft;};
		int getCantAmigos(){return this->cantAmigos;};

		string getSoftwares() // obtiene un string con los nombres de los software
		{
			string softwares = "";
			for(int i=0;i<this->cantSoft;i++){
				softwares += this->softwares[i];
				if(i != (this->cantSoft-1)){softwares += ", ";}
			}
			return softwares;
		};

		int buscarSoftware(string nameSoft) //Busca un nombre de software y retorna su posicion
		{
			int pos = -1;
			for(int i=0;i<this->cantSoft;i++)
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
			if(softwares.empty() || buscarSoftware(nameSoft) == -1){
				this->softwares.push_back(nameSoft);
				this->cantSoft++;
			}
		};

		bool borrarSoftware(string nameSoft) // elimina un software
		{
			bool esEliminado = false;
			int pos = buscarSoftware(nameSoft);
			if(pos != -1)
			{	
				string aux = softwares[cantSoft-1];
				softwares[cantSoft-1] = softwares[pos];
				softwares[pos] = aux;
				softwares.pop_back();
				cantSoft -=1;
				esEliminado = true;
			}
			return esEliminado;
		};
		string getAmigos() // obtiene un string con los nombres de los software
		{
			string listaAmigos = "";
			for(int i=0;i<this->cantAmigos;i++){
				listaAmigos += this->amigos[i].getName();
				if(i != (this->cantAmigos-1)){listaAmigos += ", ";}
			}
			return listaAmigos;
		};

		int buscarAmigo(string nombreAmigo) //Busca un nombre de software y retorna su posicion
		{
			int pos = -1;
			for(int i=0;i<this->cantAmigos;i++)
			{
				if(amigos[i].getName().compare(nombreAmigo) == 0)
				{
					pos = i;
				}
			}
			return pos;
		}

		void agregarAmigo(User amigo) //añade un software mientras no exista antes
		{
			if(amigos.empty() || buscarSoftware(amigo.getName()) == -1){
				this->amigos.push_back(amigo);
				this->cantAmigos++;
			}
		};

		bool borrarAmigo(User amigo) // elimina un software
		{
			bool esEliminado = false;
			int pos = buscarSoftware(amigo.getName());
			if(pos != -1)
			{	
				User aux = amigos[cantAmigos-1];
				amigos[cantAmigos-1] = amigos[pos];
				amigos[pos] = aux;
				amigos.pop_back();
				cantAmigos -=1;
				esEliminado = true;
			}
			return esEliminado;
		};
};
