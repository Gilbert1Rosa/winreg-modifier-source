#pragma once

#include <string>
#include <Windows.h>

extern HKEY OpenKey(std::string path);
extern void ModifyValue(HKEY key, std::string name, std::string data, DWORD type);
extern DWORD getTypeByString(std::string str);