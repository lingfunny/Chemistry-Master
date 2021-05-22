#include "items.h"

void item::clear() {
	name.clear();
	num = 0;
}

item::item() {
	clear();
}

item::item(const char* ch) {
	clear();
	name = ch;
	string p("IMG\\");
	p += name;
	p += ".jpg";
	printf("item::show->path=\"%s\"\n", p.c_str());
	wchar_t* path = multi_Byte_To_Wide_Char(p);
	IMAGE tmp;
	loadimage(&tmp, path);
	img = tmp;
	int W = img.getwidth() / (img.getheight() / H);
	loadimage(&img, path, W, H, 1);
}

item::item(const char* ch, int n) {
	clear();
	name = ch;
	num = n;
	string p("IMG\\");
	p += name;
	p += ".jpg";
	printf("item::show->path=\"%s\"\n", p.c_str());
	wchar_t* path = multi_Byte_To_Wide_Char(p);
	IMAGE tmp;
	loadimage(&tmp, path);
	img = tmp;
	int W = img.getwidth() / (img.getheight() / H);
	loadimage(&img, path, W, H, 1);
}

item::item(string s, int n) {
	clear();
	name = s;
	num = n;
	string p("IMG\\");
	p += name;
	p += ".jpg";
	printf("item::show->path=\"%s\"\n", p.c_str());
	wchar_t* path = multi_Byte_To_Wide_Char(p);
	IMAGE tmp;
	loadimage(&tmp, path);
	img = tmp;
	int W = img.getwidth() / (img.getheight() / H);
	loadimage(&img, path, W, H, 1);
}

bool item::operator<(const item& oth) {
	return name < oth.name;
}

item item::operator=(const item& oth) {
	img = oth.img;
	name = oth.name;
	num = oth.num;
	return *this;
}

void item::Show(int x, int y) {
	putimage(x, y, &img);
}

item item::CgNum(int x) {
	item New = *this;
	New.num = x;
	return New;
}

Formula::Formula() {
	C_Formula.clear();
	condition = 0;
}

Formula::Formula(const char* ch, int con) {
	C_Formula = ch;
	condition = con;
}

/*
void Formula_Map_Init(map<string, Formula>& x) {
	x.insert(make_pair("C+O2", Formula("CO2", 1)));
	x.insert(make_pair("2H2+O2", Formula("2H2O", 1)));
	x.insert(make_pair("2KMnO4", Formula("K2MnO4+MnO2+O2", 3)));
	x.insert(make_pair("2H2O2+MnO2", Formula("2H2O+O2+MnO2", 0)));	//´ß»¯¼Á
	x.insert(make_pair("2H2O", Formula("2H2+O2", 2)));
	x.insert(make_pair("2Al+6HCl", Formula("2AlCl3+3H2", 0)));
	x.insert(make_pair("Fe2O3+6HCl", Formula("2FeCl3+3H2", 0)));
	x.insert(make_pair("2Al+Fe2O3", Formula("Al2O3+2Fe", 4)));
	x.insert(make_pair("Fe+2HCl", Formula("FeCl2+H2", 0)));
}
*/
Formula Find_Formula(string s, map<string, Formula> x) {
	map<string, Formula>::iterator iter = x.find(s);
	if (iter == x.end()) {
		printf("Didn't find. %s\n", s.c_str());
		return Formula("", -1);
	}
	else {
		printf("Found! %s -> %s(%d)\n", s.c_str(), iter->second.C_Formula.c_str(), iter->second.condition);
		return iter->second;
	}
	return NULL;
}