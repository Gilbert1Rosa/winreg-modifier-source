#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <limits>
#include "Registro.h"

using namespace std;

int main(int argc, char** argv)
{
	HKEY key = NULL;
	string path = string(argv[1]);
	string value = string(argv[2]);
	string data = string(argv[3]);
	string type = string(argv[4]);

	cout << "Ruta: " << path
		<< endl
		<< "Nombre del valor: " << value
		<< endl
		<< "Valor: " << data
		<< endl
		<< "Tipo: " << type
		<< endl;

	try {
		key = OpenKey(path);
		ModifyValue(key, value, data, getTypeByString(type));
		cout << "Type: " << getTypeByString(type) << endl;
		cout << "Valor modificado..." << endl;
	} 
	catch (runtime_error& e) {
		cout << e.what() << endl;
	}

	system("pause");
	return 0;
}