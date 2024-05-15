#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void fEscribir() {
	fstream file;
	string sFrase;
	file.open("palabras.txt");


	while (sFrase != "exit")
	{
		cout << "Escribe una frase" << endl;
		cin >> sFrase;
		file << sFrase;
		cout << "todo bien" << endl;
	}
	file.close();

}

bool bVacio() {
	fstream file;
	file.open("palabras.txt");
	if (getline("palabras.txt", "1"))
	{

	}
}