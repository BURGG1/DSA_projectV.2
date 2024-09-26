#pragma once
#include <iostream>
#include<gotoxy.h>

using namespace std;
#define gotoxy coorxy;

void c(int c) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void button(int x, int y, int l, const string& a)//unang parameter x coord, syempre sunod yung y coord, yung l kung gaanon kalaki yung button, last is yung pangalan
{
	gotoxy(x, y); cout << char(201) << string(l, char(205)) << char(187); // top
	gotoxy(x, y + 1); cout << char(186); coorxy(x + l + 1, y + 1); cout << char(186);// two hori 
	gotoxy(x, y + 2); cout << char(200) << string(l, char(205)) << char(188);// bottom

	if (a.length() >= 6 && l >= 15){
		int q = a.length() / 2;
		c(7); gotoxy(x + l / q, y + 1); cout << a;
	}
	else if (a.length() <= 4 && l <= 15) {
		c(7); gotoxy(x + l / 2 - 1, y + 1); cout << a;
	}
}

void table(int h, int x, int y) {// unang parameter para sa height ng table, next is yung sa x coord, last is y coord

	gotoxy(x + 10, y + 9); cout << "Title";
	gotoxy(x + 33, y + 9); cout << "Author";
	gotoxy(x + 51, y + 9); cout << "Availability";
	gotoxy(x + 67, y + 9); cout << "Year";
	gotoxy(x + 80, y + 9); cout << "Location";
	gotoxy(x + 100, y + 9); cout << "ISBN";

	gotoxy(x + 2, y + 8); cout << char(218) << string(113, char(196)) << char(191);//Top
	gotoxy(x + 3, y + 10); cout << string(113, char(196));//TColumn
	for (int a = 0; a < h; a++)
	{
		gotoxy(x + 2, y + 9 + a); cout << char(179);//Left_Side
		gotoxy(x + 18 + 6, y + 9 + a); cout << char(179);//Title
		gotoxy(x + 38 + 11, y + 9 + a); cout << char(179);//Author
		gotoxy(x + 53 + 11, y + 9 + a); cout << char(179);//Availability/Year
		gotoxy(x + 63 + 10, y + 9 + a); cout << char(179);//Location
		gotoxy(x + 87 + 8, y + 9 + a); cout << char(179);//ISBN
		gotoxy(x + 116, y + 9 + a); cout << char(179);//Right_side
	}
	gotoxy(x + 2, h + 9 + y); cout << char(192) << string(113, char(196)) << char(217);//Bottom
}
