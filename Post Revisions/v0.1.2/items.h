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
	const int H = 50;
	string name;
	int num;
	IMAGE img;
	void clear();
	item();
	item(const char* ch);
	item(const char* ch, int n);
	item(string s, int n);
	void Show(int x, int y);
	bool operator <(const item& oth);
	item operator =(const item& oth);
	item CgNum(int x);
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

#endif // !ITEMS_H_