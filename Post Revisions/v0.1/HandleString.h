#pragma once
#ifndef HANDLE_STRING_H_
#define HANDLE_STRING_H_

#include <string>
#include <cstdlib>
#include <Windows.h>
#include <wchar.h>
using namespace std;

wchar_t* multi_Byte_To_Wide_Char(string& pKey);
string Int_To_String(int x);

#endif
