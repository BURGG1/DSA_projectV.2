#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h>
#include <gotoxy.h> // ibahin nalang din if di nagana

using namespace std;
#define gotoxy coorxy

void c(int c) { // color
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void hc(int x) { // pang hide ng cursor if needed
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 1;
	if (x == 1) {
		cursorInfo.bVisible = FALSE; // Set cursor visibility to false
	}
	else if (x == 0) {
		cursorInfo.bVisible = TRUE; // Set cursor visibility to true
	}
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

vector<string> getSuggestions(const vector<string>& suggestions, const string& input) { // pang kuha ng mga input and compare para sa intellisense
	vector<string> filteredSuggestions;
	for (const auto& suggestion : suggestions) {
		if (suggestion.find(input) == 0) { // Check if the suggestion starts with the input
			filteredSuggestions.push_back(suggestion);
		}
	}
	return filteredSuggestions;
}


int getter(string& s) { // pang get ng value
	char g[50] = {};
	int er = 1, er2 = 1;
	char d;

	for (int z = 0;;) {
		d = _getch();

		if (d == -32) {
			d = _getch();
			if (d == 72 || d == 75) {
				return  10;
			}
			else if (d == 80 || d == 77) {
				return 11;
			}
		}
		else if (d == 13) {
			g[z] = '\0';
			for (int j = 0; j < z; j++) { // Storing to string variable
				if ((g[j] >= 'a' && g[j] <= 'z') || (g[j] >= 'A' && g[j] <= 'Z') || (g[j] >= '0' && g[j] <= '9') || g[j] == ' ') {
					s += g[j];
				}
				else {
					break;
				}
			}
			return 11;
			break;
		}
		else if (d == 8 && (z >= 1 || s != "")) {
			if (er == 1 && s != "") {
				s = "";
				er = 0;
				return 12;
				break;
			}
			else {
				cout << "\b \b";
				if (z > 0) {
					g[z] = '\0';
					--z;
				}
			}
		}
		else if (((d >= 'a' && d <= 'z') || (d >= 'A' && d <= 'Z') || (d >= '0' && d <= '9') || d == ' ')) {
			if (er2 == 1) {
				s = "";
				er2 = 0;
			}
			cout << d;
			g[z] = d;
			++z;

		}
	}
}


int getterInti(string& s, int gx, int gy, int n) { // pang get din pero may intellisense
	char g[50] = {};
	int er = 1, er2 = 1;
	char d;
	string title, author, availability, year, location, isbn, line, searchBook = "";
	vector<string> sug, a;
	ifstream Record("Book_Record.txt");
	if (Record.is_open()) {
		while (getline(Record, line)) {
			stringstream ss(line);
			getline(ss, title, '\t');
			getline(ss, author, '\t');
			getline(ss, availability, '\t');
			getline(ss, year, '\t');
			getline(ss, location, '\t');
			getline(ss, isbn, '\n');
			sug.push_back(title);  // Store titles
			a.push_back(author);
		}
		Record.close();
	}

	for (int z = 0;;) {
		d = _getch();

		if (d == -32) {

			d = _getch();
			searchBook = "";
			for (int x = 0; x < 4; ++x) {
				hc(1); gotoxy(gx, (gy + 2) + x); cout << string(20, ' '); hc(0); // Clear suggestion area
			}
			if (d == 72 || d == 75) {
				return  10;
			}
			else if (d == 80 || d == 77) {
				return 11;
			}
		}
		else if (d == 13) {
			hc(0);
			searchBook = "";
			for (int x = 0; x < 4; ++x) {
				gotoxy(gx, (gy + 2) + x); cout << string(20, ' '); // Clear suggestion area
			}
			g[z] = '\0';
			for (int j = 0; j < z; j++) { // Storing to string variable
				if ((g[j] >= 'a' && g[j] <= 'z') || (g[j] >= 'A' && g[j] <= 'Z') || (g[j] >= '0' && g[j] <= '9') || g[j] == ' ') {
					s += g[j];
				}
				else {
					break;
				}
			}
			return 11;
			break;
		}
		else if (d == 8 && (z >= 1 || s != "")) {
			searchBook = "";
			for (int x = 0; x < 4; ++x) {
				hc(1); gotoxy(gx, (gy + 2) + x); cout << string(20, ' '); hc(0);// Clear suggestion area
			}
			if (er == 1 && s != "") {
				s = "";
				er = 0;
				return 12;
				break;
			}
			else {
				gotoxy(gx + z, gy); cout << "\b \b";
				if (z > 0) {
					g[z] = '\0';
					--z;
				}
			}
			gotoxy(gx + z, gy);
		}
		else if (((d >= 'a' && d <= 'z') || (d >= 'A' && d <= 'Z') || (d >= '0' && d <= '9') || d == ' ')) {
			int x = 0;
			if (er2 == 1) {
				s = "";
				er2 = 0;
			}
			gotoxy(gx + z, gy); cout << d;
			g[z] = d;
			searchBook += d;
			++z;

			auto filtered = getSuggestions(sug, searchBook);
			auto f = getSuggestions(a, searchBook);

			for (x = 0; x < 4; ++x) {
				gotoxy(gx, (gy + 2) + x); cout << string(20, ' '); // Clear suggestion area
			}
			x = 0; // Reset x for display
			if (n == 1) {// t
				for (const auto& suggestion : filtered) {
					gotoxy(gx, (gy + 2) + x); cout << suggestion; // Display suggestion
					x++;
				}
			}
			else if (n == 0) { // a
				for (const auto& suggestion : f) {
					gotoxy(gx, (gy + 2) + x); cout << suggestion; 
					x++;
				}
			}
			gotoxy(gx + z, gy);
		}
	}
}
