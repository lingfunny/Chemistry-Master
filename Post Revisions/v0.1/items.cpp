#include "items.h"

void item::clear() {
	name.clear();
	num = 0;
}

item::item() {
	clear();
}

item::item(const char* ch, int n) {
	clear();
	name = ch;
	num = n;
	string p("IMG\\");
	p += name;
	p += string(".jpg");
	wchar_t *path = multi_Byte_To_Wide_Char(p);
	loadimage(&img, path);
	int w = img.getwidth(), h = img.getheight();
	loadimage(&img, path, w / (h / 50), 50);
	//printf("Gened %s\n", ch);
}

item::item(string s, int n) {
	clear();
	name = s;
	num = n;
	string p("IMG\\");
	p += name;
	p += string(".jpg");
	wchar_t* path = multi_Byte_To_Wide_Char(p);
	loadimage(&img, path);
	int w = img.getwidth(), h = img.getheight();
	loadimage(&img, path, w / (h / 50), 50);
}

bool item::operator<(const item& oth) {
	return name < oth.name;
}

Formula::Formula() {
	C_Formula.clear();
	condition = 0;
}

Formula::Formula(const char* ch, int con) {
	C_Formula = ch;
	condition = con;
}

void Formula_Map_Init(map<string, Formula>& x) {
	x.insert(make_pair("C+O2", Formula("CO2", 1)));
	x.insert(make_pair("2H2+O2", Formula("2H2O", 1)));
	x.insert(make_pair("2KMnO4", Formula("K2MnO4+MnO2+O2", 3)));
	x.insert(make_pair("2H2O2+MnO2", Formula("2H2O+O2+MnO2", 0)));	//´ß»¯¼Á
}

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