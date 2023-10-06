//Clase Social

#include<iostream>
#include<vector>
#include "Software.h"
#include "User.h"

using namespace std;

class Social: public Software{
	private:
		vector<User> amigos;
	public:
		Social():Software(){};
		Social(string name, string dev, int minAge, float price):Software(name, dev, minAge, price){};
		void anadirAmigo(User amigo){amigos.push_back(amigo);};
};