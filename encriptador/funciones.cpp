#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

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
	string strTodo;
	for (short i = 0; i < strContenido.size(); i++)
	{
		char cLetra = strContenido[i] + sDesplazar;
		strTodo += cLetra;
	}
	file << endl << strTodo;
}
// Funcion que comprueba el antiguo checksum y llama otras fucniones
void fChecksum(string strNarchivo, string strDecrip) {
	fstream file;
	int iChecksumOrigin = 0;
	string strPrimeraLinea;
	short sVueltas = 0;
	fAbertura(strNarchivo);
	file.open(strNarchivo, ios::in);
	// Limpiar las flags
	file.clear();
	file.seekp(0);
	// Leer y descartar la primera línea
	getline(file, strPrimeraLinea);
	for (short i = 0; i < strDecrip.size(); i++) {

		// Guarda el valor ascii del caracter en una variable
		int iAsci = static_cast<int>(strDecrip[i]);
		// Suma el valor al checksum
		iChecksumOrigin += iAsci;
		
	}
	file.close();
	fAbertura(strNarchivo);
	file.open(strNarchivo, ios::in);
	// paso strlLinea (String) a int (Lo vi por internet :\)
	string strChecksum = to_string(iChecksumOrigin);
	if (strPrimeraLinea != strChecksum) {
		cout << "Aviso: El archivo ha sido modificado." << endl;
	}
	file.close();
}
// Funcion para Desencriptar
void fDecrip(string strNarchivo, string strDecrip) {
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
	
	// Bucle para descifrar char a char el contenido.
	for (short i = 0; i < strContent.size(); i++) {
		char cDecrip = strContent[i] - sDesplazar;
		cout << cDecrip;
		strDecrip += cDecrip;
	}
	cout << endl;

	file.close();
	fChecksum(strNarchivo, strDecrip);
}


// Funcion para escribir el checksum
void fChangech(int iChecksumNuevo, string strNarchivo) {
	fstream file;
	fAbertura(strNarchivo);
	// Abro el archivo en modo lectura y escritura
	file.open(strNarchivo, ios::in | ios::out);
	// Leer la primera línea y almacenar el resto del contenido
	string strPrimeraLinea;
	getline(file, strPrimeraLinea);
	string strRestoContenido;
	// Lee hasta el final del archivo
	getline(file, strRestoContenido, '\0');

	// Limpiar las flags
	file.clear();
	file.seekp(0);
	int iPrimeraLinea = stoi(strPrimeraLinea);
	iChecksumNuevo += iPrimeraLinea;
	string strChecksum = to_string(iChecksumNuevo);
	// Escribir el nuevo checksum en la primera línea
	file << strChecksum << std::endl;

	// Escribir el resto del contenido en la línea siguiente
	file << strRestoContenido;

	std::cout << "La primera linea del archivo ha sido substituida con el nuevo checksum." << std::endl;

	file.close();
}
// Funcion para hacer el nuevo checksum
void fChecksumNuevo(string strContenido, string strNarchivo,string strDecrip) {
	int iChecksumNuevo = 0;
	ifstream file;
	string strLinea;
	// Descartar la primera línea
	getline(file, strLinea);

	// Estructura que saque de internet
	stringstream strsArchivo;
	// Leer y almacenar el resto del archivo
	while (getline(file, strLinea)) {
		strsArchivo << strLinea;
	}

	// Convertir el stringstream a string
	string strArchivo = strsArchivo.str();

	strArchivo += strContenido;
	strArchivo += strDecrip;
	//Bucle que encripta char a char
	for (short i = 0; i < strArchivo.size(); i++)
	{
		int iAsci = static_cast<int>(strArchivo[i]);
		iChecksumNuevo += iAsci;
	}

	fChangech(iChecksumNuevo, strNarchivo);
}


void fEscribir(string strNarchivo, string strDecrip) {
	fstream file;
	string strContenido;
	int iChecksum = 0;
	fAbertura(strNarchivo);
	bool bExit = false;
	cout << "Escribe una frase" << endl;
	while (bExit == false)
	{
		string strFrase;
		// Leer y descartar la primera línea
		getline(cin, strFrase);
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
	// Cuando se sale del bucle, llamamos a las funciones para encriptar y para hacer el checksu,
	fEncrip(strContenido, strNarchivo);
	fChecksumNuevo(strContenido, strNarchivo, strDecrip);
	file.close();
}



// Funcion principal
void fMenu() {
	string strNarchivo = "palabras.txt";
	string strDecrip;
	if (bVacio(strNarchivo))
	{
		short sAccion;
		cout << "Quieres recuperar el contenido?" << endl;
		cout << "1. Si" << endl;
		cout << "2. No" << endl;
		cin >> sAccion;
		if (sAccion == 1)
		{
			fDecrip(strNarchivo, strDecrip);
			
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
			file << "0";
			file.close();
		}
		
	}
	else
	{
		cout << "El archivo esta vacio" << endl;
		// Insertamos una primera linea provisional para que no haya errores.
		fstream file;
		file.open(strNarchivo);
		file << "0";
		file.close();
	}
	// Llamado a la funcion de escritura
	fEscribir(strNarchivo, strDecrip);

}

