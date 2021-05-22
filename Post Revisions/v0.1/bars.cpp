#include "bars.h"

void SHOW::clear() {
	background = line = RGB(255, 255, 255);
}

void SHOW::set(COLORREF bk, COLORREF line, COLORREF txc) {
	clear();
	background = bk;
	this->line = line;
	txcolor = txc;
}

SHOW::SHOW(COLORREF bk, COLORREF line, COLORREF txc) {
	set(bk, line, txc);
}

SHOW::SHOW() {
	clear();
}

void Block::clear() {
	x = y = length = wide = size = border = 0;
	text.clear();
}

void Block::SetText(string s) {
	text = s;
	settextstyle(size, 0, _T("Consolas"));
	wchar_t* s_ = multi_Byte_To_Wide_Char(text);
	length = max(length, textwidth(s_) + border * 2);
	wide = max(wide, textheight(s_) + border * 2);
}

Block::Block() {
	clear();
}

Block::Block(int x, int y, int size, string s, int border) {
	clear();
	this->x = x;
	this->y = y;
	this->size = size;
	this->border = border;
	settextstyle(size, 0, _T("Consolas"));
	text = s;
	length = wide = -1;
	wchar_t* s_ = multi_Byte_To_Wide_Char(text);
	length = max(length, textwidth(s_) + border * 2);
	wide = max(wide, textheight(s_) + border * 2);
}

Block::Block(int x, int y, int length, int wide, int size, string s, int border) {
	clear();
	this->x = x;
	this->y = y;
	this->length = length;
	this->wide = wide;
	this->size = size;
	this->border = border;
	text = s;
	wchar_t* s_ = multi_Byte_To_Wide_Char(text);
	length = max(length, textwidth(s_) + border * 2);
	wide = max(wide, textheight(s_) + border * 2);
}

void Block::show(SHOW mode) {
	setfillcolor(mode.background);
	setfillstyle(BS_SOLID);
	if (border == 0) setlinecolor(mode.background);
	else setlinecolor(mode.line);
	setlinestyle(PS_SOLID, border);
	settextcolor(mode.txcolor);
	settextstyle(size, 0, _T("Consolas"));
	setbkmode(TRANSPARENT);
	wchar_t* s = multi_Byte_To_Wide_Char(text);
	length = max(length, textwidth(s) + border * 2);
	wide = max(wide, textheight(s) + border * 2);
	RECT r = { x, y, x + length - 1, y + wide - 1 };
	fillrectangle(x, y, x + length - 1, y + wide - 1);
	drawtext(s, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	printf("\"%s\":{%d, %d, %d, %d}\n", text.c_str(), x, y, x + length - 1, y + wide - 1);
}

bool Block::InBlock(MOUSEMSG m) {
	return (x <= m.x && m.x < x + length && y <= m.y && m.y < y + wide);
}

Button::Button() :Block() {
	Events_ID = -1;
	showed = 0;
}

Button::Button(Block x, int y):Block(x) {
	Events_ID = y;
	showed = 0;
}

void Button::Set_Events_ID(int x) {
	Events_ID = x;
}

int Button::Get_Events_ID() {
	return Events_ID;
}

void Bar::clear() {
	top = bottom = left = right = 0;
	bkcolor = WHITE;
}

Bar::Bar() {
	clear();
}

Bar::Bar(int t, int b, int l, int r, COLORREF bk) {
	top = t;
	bottom = b;
	left = l;
	right = r;
	bkcolor = bk;
}

bool Bar::InBar(MOUSEMSG m) {return (left <= m.x && m.x <= right && top <= m.y && m.y <= bottom);}

Inventory::Inventory() :Bar() {
	items.clear();
}

Inventory::Inventory(Bar s) : Bar(s) {
	items.clear();
}

void Inventory::AddItem(const char* ch, int n) {
	string s(ch);
	for (int i = 0; i < items.size(); ++i)
		if (items[i].name == s) {
			items[i].num += n;
			return;
		}
	items.push_back(item(ch, n));
}

void Inventory::AddItem(item x) {
	for(int i=0;i<items.size();++i)
		if (items[i].name == x.name) {
			items[i].num += x.num;
			return;
		}
	//printf("x.name = [%s], x.num = [%d]\n", x.name.c_str(), x.num);
	x = item(x.name, x.num);
	items.push_back(x);
}

void Inventory::show() {
	sort(items.begin(), items.end());
	setfillcolor(bkcolor);
	solidrectangle(left, top, right, bottom);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(50, 0, _T("Consolas"));
	for (int i = 0; i < min(MAX, items.size()); ++i) {
		item& T = items[i];
		int t = top + 1 + 52 * i, b = top + 52 * (i + 1) - 1;
		int l = left + 1, r = right - 1;
		HRGN rgn = CreateRectRgn(l, t, l + T.img.getwidth() / (T.img.getheight() / 50) - 1, b);
		setcliprgn(rgn);
		putimage(l, t, &T.img);
		DeleteObject(rgn);
		setcliprgn(NULL);
		RECT R = { 880, t, r, b };
		wchar_t s_[16] = { 0 };
		wsprintf(s_, L"%d", T.num);
		drawtext(s_, &R, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	setcliprgn(NULL);
}

Reaction::Reaction() :Bar() {
	reactants.clear();
}

Reaction::Reaction(Bar s) : Bar(s) {
	reactants.clear();
}

void Reaction::AddItem(item x) {
	for (int i = 0; i < reactants.size(); ++i)
		if (reactants[i].name == x.name) {
			reactants[i].num += x.num;
			return;
		}
	reactants.push_back(x);
}

void Reaction::show() {
	setfillcolor(bkcolor);
	settextstyle(50, 0, _T("Consolas"));
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	solidrectangle(left, top, right, bottom);
	sort(reactants.begin(), reactants.end());
	item plus = item("+", 0);
	int l = 0;
	for (int i = 0; i < reactants.size(); ++i) {
		printf("reactants[%d] = %s\n", i, reactants[i].name.c_str());
		if (i) {
			HRGN rgn = CreateRectRgn(l, top, l + plus.img.getwidth() / (plus.img.getheight() / 50) - 1, bottom);
			setcliprgn(rgn);
			putimage(l, top, &plus.img);
			DeleteObject(rgn);
			l += plus.img.getwidth() / (plus.img.getheight() / 50);
			// 处理“+”
		}
		item& T = reactants[i];
		//处理反应物前数字
		if (T.num > 1) {
			wchar_t s_[16] = { 0 };
			wsprintf(s_, L"%d", T.num);
			RECT R = { l, top, l + textwidth(s_),bottom };
			drawtext(s_, &R, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			l += textwidth(s_);
		}
		HRGN rgn = CreateRectRgn(l, top, l + T.img.getwidth() / (T.img.getheight() / 50) - 1, bottom);
		setcliprgn(rgn);
		putimage(l, top, &T.img);
		DeleteObject(rgn);
		setcliprgn(NULL);
		l += T.img.getwidth() / (T.img.getheight() / 50);
	}
	setcliprgn(NULL);
}
/*
 bool Inventory::InBar(MOUSEMSG m) {
	return (left <= m.x && m.x <= right && top <= m.y && m.y <= bottom);
}

 bool Button::InBlock(MOUSEMSG m) {
	return (x <= m.x && m.x < x + length && y <= m.y && m.y < y + wide);
}
*/

string Reaction::Formula() {
	string res;
	sort(reactants.begin(), reactants.end());
	for (int i = 0; i < reactants.size(); ++i) {
		if (i != 0) res += '+';
		item& x = reactants[i];
		if (x.num > 1) res += Int_To_String(x.num);
		res += x.name;
	}
	printf("Formula: %s\n", res.c_str());
	return res;
}