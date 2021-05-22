#include "Saver.h"
/*
template<typename T>
int save(T x, const char* ch) {
	ofstream fout;
	fout.open("save.dat", ios::out | ios::app | ios::binary);
	if (!fout.is_open()) {
		fout.clear();
		fout.open("save.dat", ios::out | ios::binary);
		if (!fout.is_open()) {
			printf("Cannot open the file and write \"%s\". ERROR: 101\n", ch);
			return 101;
		}
		else {
			printf("Made new file \"save.dat\", try to write \"%s\". WARNING: 100\n", ch);
		}
	}
	fout.write(ch, sizeof(ch));
	fout.write(&x, sizeof(x));
	fout.close();
	return 100;
}

template<typename T>
T read(const char* ch) {
	ifstream fin;
	fin.open("save.dat", ios::in | ios::binary);
	if (!fin.is_open()) {
		printf("Cannot open the file. ERROR:101\n");
		return NULL;
	}
	T x = NULL;
	char rd[20];
	while (fin.read(rd, sizeof(ch))) {
		if (strcmp(rd, ch) == 0) {
			fin.read(&x, sizeof(x));
		}
		else fin.read(rd, sizeof(rd));
	}
	fin.close();
	return x;
}
*/
int save(int x) {
	ofstream fout;
	fout.open("save.dat", ios::out | ios::binary);
	if (!fout.is_open()) {
		fout.clear();
		fout.open("save.dat", ios::out | ios::binary);
		if (!fout.is_open()) {
			printf("Cannot open the file. ERROR: 101\n");
			return 101;
		}
		else {
			printf("Made new file \"save.dat\". WARNING: 100\n");
		}
	}
	fout.write((char*)&x, sizeof(x));
	fout.close();
	return 100;
}

int read(){
	ifstream fin;
	fin.open("save.dat", ios::in | ios::binary);
	if (!fin.is_open()) {
		printf("Cannot open the file. ERROR:101\n");
		return NULL;
	}
	int x = NULL;
	fin.read((char*)&x, sizeof(x));
	return x;
}