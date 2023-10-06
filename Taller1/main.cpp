//Main del programa
//Jorge Bustos

#include<iostream>
#include<vector>

#include "Software.h"
#include "User.h"
#include "Juego.h"
#include "Navegador.h"
#include "Produccion.h"
#include "Social.h"
#include "Seguridad.h"
#include "Ofimatica.h"

using namespace std;

bool login(vector<User> lista, string name, string pass) //login del usuario
{
	bool logged;
	for(int i=0;i<lista.size();i++){
		if(lista[i].getName() == name){
			if(lista[i].getPassword() == pass){
				logged = true;
			}else{
				logged =  false;
			}
		}
	}
	return logged;
};

User foundUser(vector<User> listaUsuarios, string name) //busca un usuario por su nombre
{ 
	User u;
	for(int b = 0;b<listaUsuarios.size();b++){
		if(listaUsuarios[b].getName() == name){
			u = listaUsuarios[b];
		}
	}
	return u;
};

bool isValidProgram(vector<Software>listaSoft, string programa, User u) //detecta que el programa cumpla con el minimo de edad
{
	bool valido = false;
	for(int i=0;i<listaSoft.size();i++){
		if(listaSoft[i].getName() == programa){
			valido = true;
			listaSoft[i].addUser(u);
			cout<<"Programa Valido\nPrograma Anadido Correctamente"<<endl;
			break;
			}
	}
	if(!valido){cout<<"Programa no Valido\n";}
	return valido;
}

Software encontrarSoftwarePorNombre(string name, vector<Software> lista) //Busca un software por nombre
{
	Software s;
	for(int i=0;i<lista.size();i++){
		if(lista[i].getName() == name){
			s = lista[i];
		}
	}
	return s;
}

int main() {
	
	vector<Software> libreria; // Se crea la libreria
	vector<User> usuarios; //Se crea la base de datos de usuarios
	vector<string> generos = {"Accion", "Aventura", "Plataformas", "RPG", "MMO", "Puzzle", "Deportes", "FPS", "Moba", "Casino"}; //generos disponibles para clase Game
	vector<string> soluciones = {"video", "musica", "streaming", "fotos"}; //generos disponibles para clase Produccion
	vector<string> malwares = {"Ransomware", "Spyware", "botnets", "rootkits", "gusanos", "troyanos"}; //generos disponibles para clase Malware

	//Poblando Usuarios

	//admin
	User admin("coke", 19, "coke@gmail.com", "jrg666", "admin");
	usuarios.push_back(admin);

	//Niños
	User 
	nino1("Anais", 17, "", "anais8", "nino"), 
	nino2("Antonella", 14, "", "antius", "nino"), 
	nino3("Denisse", 12, "", "suripa", "nino"), 
	nino4("Marcus", 9, "", "marcus123", "nino");

	usuarios.push_back(nino1); usuarios.push_back(nino2); usuarios.push_back(nino3); usuarios.push_back(nino4);

	//Usuarios normales
	User 
	nor1("Francisco", 20, "winteroh@ucn.cl", "winteroh", "normal"), 
	nor2("John", 25, "chocolate@gmail.com", "chocolatoso", "normal"),
	nor3("Martin", 36, "univol8@yahoo.com", "torrelisa", "normal"), 
	nor4("Lima", 34, "galactico777@outlook.com", "limonconsal", "normal"),
	nor5("Mauricio", 38, "pizza.hawaiana999@hotmail.com", "normal", "nino"), 
	nor6("Paula", 51, "petty@ucn.cl", "pettyn", "normal"),
	nor7("Julian", 24, "tempo456@gmail.com", "later", "normal"), 
	nor8("Constanza", 20, "remi11@ucn.cl", "heuremi", "normal"),
	nor9("Manuel", 23, "obotn20@yahoo.com", "ayuwoki", "normal"), 
	nor10("Yulissa", 19, "invisible789@hotmail.com", "idkass", "normal");

	usuarios.push_back(nor1); usuarios.push_back(nor2); usuarios.push_back(nor3); usuarios.push_back(nor4); usuarios.push_back(nor5);
	usuarios.push_back(nor6); usuarios.push_back(nor7); usuarios.push_back(nor8); usuarios.push_back(nor9); usuarios.push_back(nor10);

	//Poblando juegos

	Game 
	j1("minecraft", "Notch", 10, 17990, "aventura"), 
	j2("gta", "Rockstar", 18, 20000, "accion"), 
	j3("hollow_knight", "bloomCherry", 14, 12000, "aventura"),
	j4("lol", "Riot Games", 14, 0, "moba"), 
	j5("WoW", "Blizzard", 14, 25990, "MMO"), 
	j6("pokemon_unite", "Nintendo", 10, 0, "moba"),
	j7("Assasins_Creed", "Ubisoft", 18, 50000, "accion"), 
	j8("Destiny_2", "Bungie Studios", 16, 50000, "MMO"), 
	j9("Super_Mario Bros", "bloomCherry", 7, 35000, "Plataformas"),
	j10("PokerStars", "Scheinberg", 18, 3990, "Casino"), 
	j11("Diablo_IV", "Blizzard", 18, 43000, "RPG"), 
	j12("Geometry_Dash", "RobTop", 9, 4500, "Plataformas"),
	j13("NBA2k", "Notch", 18, 60000, "Deportes"), 
	j14("Candy_Crush", "King", 7, 0, "Puzzle"), 
	j15("Undertale", "bloomCherry", 16, 12000, "RPG"),
	j16("WWE2k23", "Notch", 18, 45000, "Deportes"), 
	j17("Profesor_Layton", "Nintendo", 7, 40000, "Puzzle"), 
	j18("Valorant", "Riot Games", 16, 0, "FPS"),
	j19("Monopoly_Poker", "Ubisoft", 18, 0, "Casino"), 
	j20("Doom", "Bethesda", 14, 35000, "FPS");

	libreria.push_back(j1); libreria.push_back(j2); libreria.push_back(j3); libreria.push_back(j4); libreria.push_back(j5);
	libreria.push_back(j6); libreria.push_back(j7); libreria.push_back(j8); libreria.push_back(j9); libreria.push_back(j10);
	libreria.push_back(j11); libreria.push_back(j12); libreria.push_back(j13); libreria.push_back(j14); libreria.push_back(j15);
	libreria.push_back(j16); libreria.push_back(j17); libreria.push_back(j18); libreria.push_back(j19); libreria.push_back(j20);
	
	//Poblando softwares de Ofimatica
	Ofimatica
	of1("Word", "Microsoft", 7, 60000, 10), 
	of2("Excel", "Microsoft", 7, 60000, 3), 
	of3("PowerPoint", "Microsoft", 7, 50000, 5), 
	of4("Drive", "Google", 14, 0, 50), 
	of5("DropBox", "DropBox", 14, 0, 17);

	libreria.push_back(of1); libreria.push_back(of2); libreria.push_back(of3); libreria.push_back(of4); libreria.push_back(of5);

	//Poblando softwares de Produccion
	Produccion
	pr1("Youtube", "Google", 18, 0, "videos"), 
	pr2("Kick", "Tyler Faraz", 18, 3900, "streaming"), 
	pr3("Spotify", "Daniel Ek", 18, 2500, "musica"),
	pr4("Photos", "Google", 18, 0, "fotos");

	libreria.push_back(pr1); libreria.push_back(pr2); libreria.push_back(pr3); libreria.push_back(pr4);

	//Poblando softwares Navegadores
	Navegador
	nav1("Opera", "Opera", 0, 0), 
	nav2("Chrome", "Google", 0, 0);

	libreria.push_back(nav1); libreria.push_back(nav2);

	//Poblando softwares de Seguridad
	Seguridad
	seg1("Malwarebytes", "Marcin Kleczynski", 13, 10000, "Ransomware"),
	seg2("Spybot_Search", "Patrick Michael", 13, 50000, "Spyware"),
	seg3("Norton_Power", "Peter Norton", 13, 16000, "botnets"),
	seg4("Sophos_Anti-Rootkit", "Kaspersky Lab ", 13, 26785, "fotrootkitsos"),
	seg5("Security_Essentials", "Microsoft", 13, 0, "gusanos"),
	seg6("ESET_NOD32", "Miroslav Trnka", 13, 27499, "troyanos");

	libreria.push_back(seg1); libreria.push_back(seg2); libreria.push_back(seg3);
	libreria.push_back(seg4); libreria.push_back(seg5); libreria.push_back(seg6);
	
	//Poblando Softwares sociales
	Social
	soc1("Tinder", "Renate Nyborg", 18, 0), 
	soc2("IAmigos", "Cokke", 10, 0);

	libreria.push_back(soc1); libreria.push_back(soc2);

	
	bool isLogged = false, isQuit = false;
	string nombre, contrasena;
	User user;
	do
	{
		while(!isLogged)	//login
		{
			cout<<"\nIngrese su nombre: ";cin>>nombre;
			cout<<"\nIngrese su contrasena: ";cin>>contrasena;
			isLogged = login(usuarios, nombre, contrasena);
			
			if(!isLogged)
			{
				cout<<"Intente nuevamente"<<endl;
			}
			else
			{
				cout<<"Acceso correcto"<<endl;
				cout<<"Bienvenido "<<nombre<<", Que desea realizar?"<<endl;
				user = foundUser(usuarios, nombre);
			}
		}
		vector<Software> posiblesProgramas; //vector de programas validos para el usuario
		for(int i=0;i<libreria.size();i++)
		{
			if(user.getAge() >= libreria[i].getMinAge())
			{
				posiblesProgramas.push_back(libreria[i]);
			}
		}

		string nuevoPrograma = "";//variables para el switch
		int cant=0;

		cout<<"\n\t-Menu-"<<endl; //menu
		cout<<"1)ver mis programas\n2)ver programas en la base de datos\n3)agregar programa\n0)Logout\n";

		int opcion;cin>>opcion;

		switch(opcion)
		{
			case 1://muestra los programas agregados
				if(user.getCant() != 0){cout<<user.getSoftwares()<<endl;}
				else{cout<<"No tiene programas agregados\n";}
				break;
			case 2://muestra los softwares que puede acceder
				for(int j=0;j<posiblesProgramas.size();j++){cout<<posiblesProgramas[j].getName()<<endl;}
				break;
			case 3://Agrega un programa a la libreria propia
				cout<<"Ingrese nombre del Programa a agregar: \n";cin>>nuevoPrograma;
				if(isValidProgram(posiblesProgramas, nuevoPrograma, user)){user.agregarSoftware(nuevoPrograma);}
				break;
			case 4://eliminar un programa de la libreria propia
				break;
			case 5://añadir un programa a la biblioteca general
				break;
			case 6://eliminar un programa de la biblioteca general
				break;
			case 0:
				cout<<"Ha salido Correctamente";
				isLogged = false;
				int salir = 0;
				while(salir<1 || salir>2)
				{
					cout<<"\nQuiere (1)iniciar sesion con otra cuenta o (2)cerrar el programa?\n";cin>>salir;
				}
				if(salir == 2){isQuit = true;}
				break;
		}
	} while (!isQuit);
};

