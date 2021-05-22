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
	//printf("\"%s\":{%d, %d, %d, %d}\n", text.c_str(), x, y, x + length - 1, y + wide - 1);
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
	begin = end = 0;
	items.clear();
}

Inventory::Inventory(Bar s) : Bar(s) {
	begin = end = 0;
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
	items.push_back(x);
	//push_back的item，必须存在img对象
}

void Inventory::show() {
	sort(items.begin(), items.end());
	end = begin + min(MAX, items.size() - begin);
	setfillcolor(bkcolor);
	solidrectangle(left, top, right, bottom);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(50, 0, _T("Consolas"));
	for (int i = begin; i < end; ++i) {
		item& T = items[i];
		int t = top + 1 + (i - begin) * 52;
		T.Show(0, t);
		//printf("Showed [%s], i = %d\n", T.name.c_str(), i);
		RECT R = { 880, t, right, t + 51 };
		wchar_t s_[16] = { 0 };
		wsprintf(s_, L"%d", T.num);
		drawtext(s_, &R, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	if (begin) {
		PgUp.showed = 1;
	}
	else {
		PgUp.showed = 0;
	}
	if (end < items.size()) {
		PgDn.showed = 1;
	}
	else {
		PgDn.showed = 0;
	}
	//printf("PgUp.showed = %d\n", PgUp.showed);
	//printf("PgUp={ %d, %d, %d, %d }\n", PgUp.x, PgUp.x + PgUp.length - 1, PgUp.y, PgUp.y + PgUp.wide - 1);
	PgUp.show(SHOW(bkcolor, bkcolor, PgUp.showed ? BLACK : RGB(149, 149, 149)));
	PgDn.show(SHOW(bkcolor, bkcolor, PgDn.showed ? BLACK : RGB(149, 149, 149)));
}

void Inventory::PageUp() {
	begin -= MAX;
}

void Inventory::PageDown() {
	begin += MAX;
}

Reaction::Reaction() :Bar() {
	reactants.clear();
	items_Rect.clear();
}

Reaction::Reaction(Bar s) : Bar(s) {
	reactants.clear();
	items_Rect.clear();
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
	setfillcolor(BACKGROUND_COLOR);
	settextstyle(TEXT_SIZE, 0, _T("Consolas"));
	settextcolor(TEXT_COLOR);
	setbkmode(TRANSPARENT);
	setlinecolor(LINE_COLOR);
	setlinestyle(PS_SOLID, BORDER_SIZE);
	fillrectangle(left, top, right, bottom);
	sort(reactants.begin(), reactants.end());
	items_Rect.clear();
	int l = BORDER_SIZE;
	for (int i = 0; i < reactants.size(); ++i) {
		item& T = reactants[i];
		printf("reactants[%d] = %s:%d\n", i, reactants[i].name.c_str(), T.num);
		if (i) {
			wchar_t s_[16] = { 0 };
			wsprintf(s_, L"+");
			RECT R = { l, top + BORDER_SIZE, l + textwidth(s_), bottom - BORDER_SIZE };
			drawtext(s_, &R, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			l += textwidth(s_);
			// 处理“+”
		}
		int l_ = l;
		//处理反应物前数字
		if (T.num > 1) {
			wchar_t s_[16] = { 0 };
			wsprintf(s_, L"%d", T.num);
			RECT R = { l, top + BORDER_SIZE, l + textwidth(s_),bottom - BORDER_SIZE };
			drawtext(s_, &R, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			l += textwidth(s_);
		}
		T.Show(l, top + BORDER_SIZE);
		l += T.img.getwidth();
		items_Rect.push_back(Rect(top, l_, l, bottom));
	}
	setcliprgn(NULL);
}

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

void Rect::clear() {
	top = left = bottom = right = 0;
}

Rect::Rect() {
	clear();
}

Rect::Rect(int t, int l, int r, int b) {
	top = t;
	left = l;
	right = r;
	bottom = b;
}

bool Rect::InRect(MOUSEMSG m) {
	return (top <= m.y && m.y <= bottom && left <= m.x && m.x <= right);
}