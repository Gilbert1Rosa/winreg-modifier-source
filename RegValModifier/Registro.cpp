#include "Registro.h"
#include <iostream>

using namespace std;

bool beginsWith(std::string source, std::string toFind);

HKEY getRoot(std::string path);
std::string getSubPath(std::string path);

HKEY OpenKey(std::string path)
{
	HKEY key;
	LONG error;
	error = RegOpenKeyEx(getRoot(path), getSubPath(path).c_str(), 0, KEY_ALL_ACCESS, &key);
	cout << "subpath: " << getSubPath(path) << endl;
	if (error != 0) {
		throw runtime_error("No se pudo abrir la clave");
	}
	return key;
}

void ModifyValue(HKEY key, 
                 std::string name, 
                 std::string data, 
                 DWORD type)
{
	LONG error = RegSetValueEx(key,
		name.c_str(),
		NULL,
		type,
		(CONST BYTE*) data.c_str(),
		data.size() + 1);
	if (error != 0) {
		throw runtime_error("No se pudo modificar el valor;");
	}
}

HKEY getRoot(std::string path)
{
	string rootStr = path;
	HKEY root = 0;

	if (beginsWith(rootStr, "HKEY_LOCAL_MACHINE")) {
		root = HKEY_LOCAL_MACHINE;
	}
	else if (beginsWith(rootStr, "HKEY_CLASSES_ROOT")) {
		root = HKEY_CLASSES_ROOT;
	}
	else if (beginsWith(rootStr, "HKEY_CURRENT_USER")) {
		root = HKEY_CURRENT_USER;
	}
	else if (beginsWith(rootStr, "HKEY_USERS")) {
		root = HKEY_USERS;
	}
	else if (beginsWith(rootStr, "HKEY_CURRENT_CONFIG")) {
		root = HKEY_CURRENT_CONFIG;
	}
	return root;
}

std::string getSubPath(std::string path)
{
	string subPath = path;
	int comienzo = subPath.find_first_of("\\") + 1;
	return subPath.substr(comienzo, subPath.size());
}

DWORD getTypeByString(std::string str)
{
	int type = 0;
	if (str == "REG_BINARY") {
		type = REG_BINARY;
	}
	else if (str == "REG_DWORD") {
		type = REG_DWORD;
	}
	else if (str == "REG_DWORD_LITTLE_ENDIAN") {
		type = REG_DWORD_LITTLE_ENDIAN;
	}
	else if (str == "REG_DWORD_BIG_ENDIAN") {
		type = REG_DWORD_BIG_ENDIAN;
	}
	else if (str == "REG_EXPAND_SZ") {
		type = REG_EXPAND_SZ;
	}
	else if (str == "REG_LINK") {
		type = REG_LINK;
	}
	else if (str == "REG_MULTI_SZ") {
		type = REG_MULTI_SZ;
	}
	else if (str == "REG_NONE") {
		type = REG_NONE;
	}
	else if (str == "REG_QWORD") {
		type = REG_QWORD;
	}
	else if (str == "REG_QWORD_LITTLE_ENDIAN") {
		type = REG_QWORD_LITTLE_ENDIAN;
	}
	else if (str == "REG_SZ") {
		type = REG_SZ;
	}
	return type;
}


bool beginsWith(std::string source, std::string toFind)
{
	string sbstr = source.substr(0, toFind.size());
	return sbstr == toFind;
}