#include <iostream>
#include <string>
#include <fstream>

using namespace std;


bool bVacio() {
	fstream file;
	file.open("palabras.txt");
	string primeraLinea;
	getline(file, primeraLinea);
	if (primeraLinea.empty()) {
		return false;
		cout << "vacio" << endl;
	}
	else {
		return true;
		cout << "no vacio" << endl;
	}
}

void fAbertura() {
	fstream file;
	file.open("palabras.txt");
	if (!file.is_open()) {
		cout << "No se pudo abrir el archivo" << endl;
	}
	else
	{
		cout << "Todo bien" << endl;
	}

}

void fEscribir() {
	fstream file;

	if (bVacio())
	{
		short sAccion;
		cout << "Quieres recuperar el contenido?" << endl;
		cout << "1. Si" << endl;
		cout << "2. No" << endl;
		cin >> sAccion;
		if (sAccion == 1)
		{
			fAbertura();
			string strLinea; 
			while (getline(file, strLinea)) { 
				cout << strLinea << endl; 
			}
			file.close(); 
		}
		else if (sAccion == 2)
		{
			fAbertura();
			string sLinea;
			while (getline(file, sLinea)) {
				sLinea.pop_back();
			}
		}
		
	}
	string sFrase; 
	file.open("palabras.txt", ios::app); 
	while (sFrase != "exit")
	{
		cout << "Escribe una frase" << endl;
		cin >> sFrase;
		file << sFrase << std::endl;
		cout << "todo bien" << endl;
	}
	
	file.close();
}

