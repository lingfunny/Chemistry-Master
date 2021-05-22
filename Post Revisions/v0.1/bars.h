#pragma once
#ifndef BARS_H_
#define BARS_H_

#include <graphics.h>
#include <vector>
#include <algorithm>
#include <string>
#include "items.h"
#include "HandleString.h"
using namespace std;

class SHOW {
	// 显示Block设置
public:
	COLORREF background, line, txcolor;
	void clear();
	void set(COLORREF bk, COLORREF line, COLORREF txc);
	SHOW();
	SHOW(COLORREF bk, COLORREF line, COLORREF txc);
};

class Block {
	// 方块类显示
public:
	int x, y;
	int length, wide;
	int size, border, ID;
	string text;
	void clear();
	void SetText(string s);
	Block();
	Block(int x, int y, int size, string s, int border = 0);
	Block(int x, int y, int length, int wide, int size, string s, int border = 0);
	bool InBlock(MOUSEMSG m);
	void show(SHOW mode=SHOW());
};

class Button :public Block {
private:
	int Events_ID;
public:
	void Set_Events_ID(int x);
	int Get_Events_ID();
	Button();
	Button(Block x, int y);
	int showed;
};

class Bar {
public:
	int top, bottom, left, right;
	COLORREF bkcolor;
	void clear();
	Bar();
	Bar(int t, int b, int l, int r, COLORREF bk = WHITE);
	bool InBar(MOUSEMSG m);
};

class Inventory : public Bar {
private:
	const int MAX = 4;
	const int LENGTH = 1080;
	const int WIDTH = 50;
public:
	vector <item> items;
	Inventory();
	Inventory(Bar s);
	void AddItem(const char* ch, int n);
	void AddItem(item x);
	void show();
};

class Reaction :public Bar {
private:
	const int MAX = 4;
public:
	vector <item> reactants;
	Reaction();
	Reaction(Bar s);
	void AddItem(item x);
	void show();
	string Formula();
};

#endif // !BARS_H_