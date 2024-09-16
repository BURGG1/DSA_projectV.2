#include <iostream>
#include <string>
#include <fstream>
#include <gotoxy.h>
#include <conio.h>
using namespace std;

#define gotoxy coorxy

void c(int c) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void button(int x, int y, int l,const string& a)//unang parameter x coord, syempre sunod yung y coord, yung l kung gaanon kalaki yung button, last is yung pangalan
 {
	coorxy(x, y); cout << char(201) << string(l, char(205)) << char(187);
	for (int a = 0; a < 1; a++)
	{
		coorxy(x, y + 1); cout << char(186);
		coorxy(x + l + 1, y + 1); cout << char(186);
	}
	coorxy(x, y + 2); cout << char(200) << string(l, char(205)) << char(188);

	if (a.length() > 6)
	{
		c(7);coorxy(x + l / 2 - 2, y + 1); cout << a;
	}
	else {
		c(7);coorxy(x + l / 2, y + 1); cout << a;
	}
}

void table(int h, int x, int y) {// unang parameter para sa height ng table, next is yung sa x coord, last is y coord

	gotoxy(x + 6, y + 9); cout << "Title";
	gotoxy(x + 25, y + 9); cout << "Author";
	gotoxy(x + 40, y + 9); cout << "Availability";
	gotoxy(x + 56, y + 9); cout << "Year";
	gotoxy(x + 67, y + 9); cout << "Location";
	gotoxy(x + 90, y + 9); cout << "ISBN";

	gotoxy(x + 2, y + 8); cout << char(218) << string(101, char(196)) << char(191);//Top
	gotoxy(x + 3, y + 10); cout << string(101, char(196));//TColumn
	for (int a = 0; a < h; a++)
	{
		gotoxy(x + 2, y + 9 + a); cout << char(179);//Left_Side
		gotoxy(x + 18, y + 9 + a); cout << char(179);//Title
		gotoxy(x + 38, y + 9 + a); cout << char(179);//Author
		gotoxy(x + 53, y + 9 + a); cout << char(179);//Availability/Year
		gotoxy(x + 63, y + 9 + a); cout << char(179);//Location
		gotoxy(x + 85, y + 9 + a); cout << char(179);//ISBN
		gotoxy(x + 104, y + 9 + a); cout << char(179);//Right_side
	}
	gotoxy(x + 2, h + 9 + y); cout << char(192) << string(101, char(196)) << char(217);//Bottom
}









//int main() // add practice || not yet done and tentative to use 
//{
//	
//	struct Book {
//		string title, author, availability, year, callno, rent, name;
//	}book;
//	int counter = 1;
//
//
//
//	//ADD
//s:
//	gotoxy(45, 2); cout << "Press the Enter key first to Add!";
//
//	table(15, 0, 0); button(105, 18, 10, "ADD");button(105, 22, 10, "BACK");
//
//	if (counter == 1)// title
//	{
//		gotoxy(6, 11);
//	}
//	else if (counter == 2)// author
//	{
//		gotoxy(25, 11);
//	}
//	else if (counter == 3) // availability
//	{
//		gotoxy(40, 11);
//	}
//	else if (counter == 4)// year
//	{
//		gotoxy(56, 11);
//	}
//	else if (counter == 5)// location
//	{
//		gotoxy(65, 11);
//	}
//	else if (counter == 6)// ISBN
//	{
//		gotoxy(87, 11);
//	}
//	else if (counter == 7)
//	{
//		c(4);
//		button(105, 22, 10, "BACK");
//		c(7);
//	}
//	else if (counter == 8)
//	{
//		c(4);
//		button(105, 18, 10, "ADD");
//		c(7);
//	}
//
//	switch (_getch()){
//	case 224:
//		switch (_getch()) {
//		case 72:case 75:
//			if (counter <= 1){counter = 7;}
//			else counter--;
//			break;
//		case 80:case 77:
//			if (counter > 6) { counter = 1; }
//			else counter++;
//			break;
//		}
//		goto s;
//		break;
//	case 13:
//		switch (counter)
//		{
//		case 1:
//			gotoxy(6, 11); getline(cin, book.title);
//			counter++;
//		case 2:
//			gotoxy(25, 11); getline(cin, book.author);
//			counter++;
//		case 3:
//			gotoxy(40, 11); getline(cin, book.author);
//			counter++;
//		case 4:
//			gotoxy(56, 11); getline(cin, book.author);
//			counter++;
//		case 5:
//			gotoxy(65, 11); getline(cin, book.author);
//			counter++;
//		case 6:
//			gotoxy(87, 11); getline(cin, book.author);
//			counter = 8;
//			goto s;
//		    break;
//		case 7:
//			system("cls");
//			cout << "dito ang back";
//			break;
//		case 8:
//			system("cls");
//			cout << book.title;
//			cout << book.author;
//			break;
//
//
//		}
//	}
//
//
//
//
//
//
//
//
//  button(80, 25, 10, "Ok");
//}  //ADD