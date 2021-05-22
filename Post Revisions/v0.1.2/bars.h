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
static const int REACTANTS_X = 2 << 10;
static const int In_PgUp = 2 << 11;
static const int In_PgDn = 2 << 12;

class SHOW {
	// 显示Block设置
public:
	COLORREF background, line, txcolor;
	void clear();
	void set(COLORREF bk, COLORREF line, COLORREF txc);
	SHOW();
	SHOW(COLORREF bk, COLORREF line, COLORREF txc);
	/*
	- 参数1：背景颜色
	- 参数2：线条（边框）颜色
	- 参数3：文字颜色
	*/
};

class Rect {
	// 方块区域
public:
	int top, left, right, bottom;
	void clear();
	Rect();
	Rect(int t, int l, int r, int b);
	bool InRect(MOUSEMSG m);
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
	Button(Block x, int y = 0);
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
	int begin, end;
	Button PgUp, PgDn;
	vector <item> items;
	Inventory();
	Inventory(Bar s);
	void AddItem(const char* ch, int n);
	void AddItem(item x);
	void show();
	void PageDown();
	void PageUp();
};

class Reaction :public Bar {
private:
	static const int MAX = 4;
	static const int TEXT_SIZE = 75;
	static const int BORDER_SIZE = 2;
	static const COLORREF BACKGROUND_COLOR = RGB(230, 230, 230);
	static const COLORREF LINE_COLOR = BLACK;
	static const COLORREF TEXT_COLOR = BLACK;
public:
	vector <item> reactants;
	vector <Rect> items_Rect;
	Reaction();
	Reaction(Bar s);
	void AddItem(item x);
	void show();
	string Formula();
};

#endif // !BARS_H_