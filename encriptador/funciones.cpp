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
}

void fEncrip(string strContenido) {
	short sDesplazar = 26;
	fstream file;
	file.open("palabras.txt", ios::app);
	for (short i = 0; i < strContenido.size(); i++)
	{
		char cLetra = strContenido[i] + sDesplazar;
		file << cLetra;
	}
}

void fDecrip() {
	fAbertura();
	fstream file;
	file.open("palabras.txt", ios::in);
	string strLinea;
	short sDesplazar = 26;
	while (getline(file, strLinea)) {
		for (short i = 0; i < strLinea.size(); i++)
		{
			char cDecrip = strLinea[i] - sDesplazar;
			cout << cDecrip;
		}
	}
	file.close();
}

void fEscribir() {
	fstream file;
	string strContenido;
	
	
	fAbertura();
	bool bExit = false;
	while (bExit == false)
	{
		string strFrase;
		cout << "Escribe una frase" << endl;
		getline(cin, strFrase);
		if (strFrase == "exit")
		{
			bExit = true;
		}
		else
		{
			strContenido += strFrase + '\n';
		}
		fEncrip(strContenido);
	}

	file.close();

}


void fChecksum() {
	fAbertura();
	fstream file;
	file.open("palabras.txt", ios::in);

}


void fMenu() {

	if (bVacio())
	{
		short sAccion;
		cout << "Quieres recuperar el contenido?" << endl;
		cout << "1. Si" << endl;
		cout << "2. No" << endl;
		cin >> sAccion;
		if (sAccion == 1)
		{
			fDecrip();
		}
		else if (sAccion == 2)
		{
			fAbertura();
			fstream file;
			file.open("palabras.txt", std::ofstream::out | std::ofstream::trunc);
			file.close();
		}
		
	}
	
	fEscribir();

}

