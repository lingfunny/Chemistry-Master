#pragma once
#ifndef ITEMS_H_
#define ITEMS_H_

#include <graphics.h>
#include <map>
#include <string>
#include <utility>
#include "HandleString.h"
using namespace std;

struct item {
	string name;
	int num;
	IMAGE img;
	void clear();
	item();
	item(const char* ch, int n);
	item(string s, int n);
	bool operator <(const item& oth);
};

struct Formula {
	string C_Formula;
	int condition;
	/*
	* condition
	- 0: 无条件
	- 1: 点燃
	- 2: 通电
	- 3: 加热
	- 4: 高温
	*/
	Formula();
	Formula(const char* ch, int con=0);
};

Formula Find_Formula(string s, map<string, Formula> x);
void Formula_Map_Init(map<string, Formula>& x);

#endif // !ITEMS_H_