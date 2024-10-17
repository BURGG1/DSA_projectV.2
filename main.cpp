#include <iostream>
#include <fstream>
#include <gotoxy.h>
#include "options.cpp"

using namespace std;

int main() {

	int ct = 0;
top:
	int size = 0;
	fstream Record("trial_Book_Record.txt");
	if (Record.is_open()) {
		string line;
		while (getline(Record, line)) {
			++size;
		}
	}Record.close();

	bookRecord(size);

	gotoxy(0, 29);	system("pause");



}

