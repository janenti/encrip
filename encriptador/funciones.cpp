#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Funcion que verifica si el archivo esta vacio
bool bVacio(string strNarchivo) {
	fstream file;
	file.open(strNarchivo);
	string primeraLinea;
	getline(file, primeraLinea);
	if (primeraLinea.empty()) {
		return false;
	}
	else {
		return true;
	}
}
// Funcion que verifica si se puede abrir el archivo
void fAbertura(string strNarchivo) {
	fstream file;
	file.open(strNarchivo);
	if (!file.is_open()) {
		cout << "No se pudo abrir el archivo" << endl;
	}
}
// Funcion para encriptar
void fEncrip(string strContenido, string strNarchivo) {
	short sDesplazar = 26;
	fstream file;
	file.open(strNarchivo, ios::app);
	//Bucle que encripta char a char
	for (short i = 0; i < strContenido.size(); i++)
	{
		char cLetra = strContenido[i] + sDesplazar;
		file << cLetra;
	}
}
// Funcion para Desencriptar
void fDecrip(string strNarchivo) {
	fAbertura(strNarchivo);
	fstream file;
	file.open("palabras.txt", ios::in);
	string strLinea;
	short sDesplazar = 26;
	string strContent;

	// Leer y descartar la primera linea
	if (getline(file, strLinea)) {
		// Leer desde la segunda linea hasta el final del archivo
		while (getline(file, strLinea)) {
			strContent += strLinea;
		}
	}
	// Bucle para descifraf char a char el contenido.
	for (short i = 0; i < strContent.size(); i++) {
		char cDecrip = strContent[i] - sDesplazar;
		cout << cDecrip;
	}
	cout << endl;

	file.close();
}
void fCverif(int iChecksum, string strNarchivo) {
	fstream file;
	string strLinea;
	fAbertura(strNarchivo);
	file.open(strNarchivo, ios::in);
	// paso strlLinea (Numero entero) a int (Lo vi por internet :\)
	int checksumArchivo = stoi(strLinea);
	if (iChecksum != checksumArchivo) {
		cout << "Aviso: El archivo ha sido modificado." << endl;
	}
	file.close();

	cout << "El checksum se ha verificado y actualizado correctamente." << endl;
}

// Funcion para escribir el checksum
void fChangech(int iChecksum, string strNarchivo) {
	fstream file;
	fAbertura(strNarchivo);
	file.open(strNarchivo);
	file << iChecksum;
	file.close();
}

void fChecksum(string strNarchivo, int iChecksum) {
	fstream file;
	string strLinea;
	string strContent;
	fAbertura(strNarchivo);
	file.open(strNarchivo, ios::in);
	// Leer y descartar la primera línea
	if (getline(file, strLinea)) {
		// Leer desde la segunda línea hasta el final del archivo
		while (getline(file, strLinea)) {
			strContent += strLinea;
		}
	}
	for (short i = 0; i < strContent.size(); i++) {

		// Guarda el valor ascii del caracter en una variable
		int iAsci = static_cast<int>(strContent[i]);
		// Suma el valor al checksum
		iChecksum + iAsci;
	}
	//Llama a la funcion que inserta y verifica el checksum
	fCverif(iChecksum, strNarchivo);
	file.close();
}
void fEscribir(string strNarchivo) {
	fstream file;
	string strContenido;
	fAbertura(strNarchivo);
	int iChecksum = 0;
	bool bExit = false;
	while (bExit == false)
	{
		string strFrase;
		cout << "Escribe una frase" << endl;
		// Leer y descartar la primera línea
		if (getline(file, strFrase)) {
			// Leer desde la segunda línea hasta el final del archivo
			getline(file, strFrase);
			// Si la palabra es exit, se termina el programa.
			if (strFrase == "exit")
			{
				bExit = true;
			}
			// Si la frase no es exit, introduce la frase a un string concatenandola con \n para que al desencriptar, haya saltos de linea
			else
			{
				strContenido += strFrase + '\n';
			}
		}
	}
	// Cuando se sale del bucle, llamamos a las funciones para encriptar y para hacer el checksu,
	fChecksum(strNarchivo, iChecksum);
	fEncrip(strContenido, strNarchivo);
	fChangech(iChecksum, strNarchivo);
	file.close();
}



// Funcion principal
void fMenu() {
	string strNarchivo = "palabras.txt";
	if (bVacio(strNarchivo))
	{
		short sAccion;
		cout << "Quieres recuperar el contenido?" << endl;
		cout << "1. Si" << endl;
		cout << "2. No" << endl;
		cin >> sAccion;
		if (sAccion == 1)
		{
			fDecrip(strNarchivo);
		}
		else if (sAccion == 2)
		{
			fAbertura(strNarchivo);
			fstream file;
			// Esta linea esta sacada de StackOverflow
			file.open(strNarchivo, std::ofstream::out | std::ofstream::trunc);
			file.close();
			// Insertamos una primera linea provisional para que no haya errores.
			file.open(strNarchivo);
			file << "Checksum0";
		}
		
	}
	else
	{
		cout << "El archivo esta vacio";
		// Insertamos una primera linea provisional para que no haya errores.
		fstream file;
		file.open(strNarchivo);
		file << "Checksum0";
	}
	// Llamado a la funcion de escritura
	fEscribir(strNarchivo);

}

