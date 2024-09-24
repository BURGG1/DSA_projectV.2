#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include<sstream>
#include <gotoxy.h>
#include <conio.h>
using namespace std;

#define gotoxy coorxy

void c(int c) { // color lang ya
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void button(int x, int y, int l, const string& a)//unang parameter x coord, syempre sunod yung y coord, yung l kung gaanon kalaki yung button, last is yung pangalan
{
	coorxy(x, y); cout << char(201) << string(l, char(205)) << char(187); // top
	coorxy(x, y + 1); cout << char(186);coorxy(x + l + 1, y + 1); cout << char(186);// two hori 
	coorxy(x, y + 2); cout << char(200) << string(l, char(205)) << char(188);// bottom

	if (a.length() >= 6 && l >= 15)
	{
		int i = a.length() / 2;
		c(7); coorxy(x + l / i, y + 1); cout << a;
	}
	else if (a.length() <= 4 && l <= 15) {
		c(7); coorxy(x + l / 2 - 1, y + 1); cout << a;
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
		gotoxy(x + 38 + 11,  y + 9 + a); cout << char(179);//Author
		gotoxy(x + 53 + 11, y + 9 + a); cout << char(179);//Availability/Year
		gotoxy(x + 63 + 10, y + 9 + a); cout << char(179);//Location
		gotoxy(x + 87 + 8, y + 9 + a); cout << char(179);//ISBN
		gotoxy(x + 116, y + 9 + a); cout << char(179);//Right_side
	}
	gotoxy(x + 2, h + 9 + y); cout << char(192) << string(113, char(196)) << char(217);//Bottom
}


//int main() // try lang // susccesss!!
//{
//
//	char adminuser[] = "Admin", adminpass[] = "Adminpass", user[] = "User1", userpass[] = "Userpass";
//	char username[32] = {}, password[32] = {};
//
//	char d;
//	gotoxy(45, 9);
//	for (int i = 0;;) { // username
//		d = _getch();
//
//		if ((d >= 'a' && d <= 'z') || (d >= 'A' && d <= 'Z') || (d >= '0' && d <= '9' || d == ' ')) {
//			cout << d;
//			username[i] = d;
//			++i;
//   		}
//		else if (d == 8 && i >= 1) {
//			cout << "\b \b";
//			username[--i] = '\0';
//		}
//		else if (d == 13) {
//			username[i] = '\0';
//			break;
//		}
//
//	}
//	gotoxy(45, 10);
//	for (int a = 0;;){//password!
//		d = _getch();
//		if ((d >= 'a' && d <= 'z') || (d >= 'A' && d <= 'Z') || (d >= '0' && d <= '9' || d == ' ')) {
//			cout << "*";
//			password[a] = d;
//			++a;
//		}
//		else if (d == 8 && a >= 1) {
//			cout << "\b \b";
//			username[--a] = '\0';
//		}
//		else if (d == 13) {
//			username[a] = '\0';
//			break;
//		}
//
//
//	}
//
//
//
//	cout << endl;
//	cout << username;
//}

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


int main() { // *di pa to tapos 

	string searchbook[32];
	string search;
	char d;
	bool print = false;
	int counter = 0;
M:
	gotoxy(70, 2); cout << char(218) << string(37, char(196)) << char(191);
	gotoxy(70, 3); cout << char(179); gotoxy(71, 3); cout << "Search:" << char(179); gotoxy(108, 3); cout << char(179); // search bar
	gotoxy(70, 4); cout << char(192) << string(37, char(196)) << char(217);

	table(10, 1, 1);
	/*c(7); button(4, 5, 14, "A-Z");*/
	c(7); button(60, 25, 15, "Delete");
	c(7); button(80, 25, 14, "Edit");
	c(7); button(99, 25, 14, "Back");
	gotoxy(80, 3); cout << string(15, ' ');


	/*for (int i = 0;;) { // search to na nagagamit din yung arrow key, sayang lang di makapag search kahit nakukuha naman yung input || tentative to use
		switch (counter) {
		case 0:
			gotoxy(80, 3);
			for (int j = 0;;) {
				d = _getch();
				if (d == -32) {
					d = _getch();
					if (d == 72 || d == 75) {
						counter = 3;
						break;
					}
					else if (d == 80 || d == 77) {
						counter++;
						break;
					}
				}
				else if (d == 8 && j >= 1) {
					cout << "\b \b";
					searchbook[--j] = '\0';
				}
				else if ((d >= 'A' && d <= 'Z') || (d >= 'a' && d <= 'z') || d == ' ' && j < 32) {
					coorxy(80 + j, 3); cout << d;
					searchbook[j] = d;
					++j;
				}
				else if (d == 13) {
					counter++;
					searchbook[j] = '\0';
					for (int k = 0; k < 32; k++) {
						search += searchbook[k];
					}
					gotoxy(1, 1); cout << search;
					ifstream Record("Book_Record.txt");
					if (Record.is_open()) {
						string title, author, availability, year, location, callno;
						while (getline(Record, title)) {
							getline(Record, author);
							getline(Record, availability);
							getline(Record, year);
							getline(Record, location);
							getline(Record, callno);
							if (title == search || author == search) {

								gotoxy(6, 12); cout << title << endl;
								gotoxy(28, 12); cout << author << endl;
								gotoxy(52, 12); cout << availability << endl;
								gotoxy(63, 12); cout << year << endl;
								gotoxy(82, 12); cout << location << endl;
								gotoxy(102, 12); cout << callno << endl;

								print = true;

							}
						}
						Record.close();
					}
					else {
						if (!print) {

							cout << "Unable to open file!" << endl;
						}

					}
					break;
				}
			}
			break;
		case 1:
			c(4); button(60, 25, 15, "");
			for (int j = 0;;) {
				d = _getch();
				if (d == -32) {
					d = _getch();
					if (d == 72 || d == 75) {
						counter--;
						break;
					}
					else if (d == 80 || d == 77) {
						counter++;
						break;
					}
				}
			}
			goto M;
			break;
		case 2:
			c(4); button(80, 25, 14, "");
			for (int j = 0;;) {
				d = _getch();
				if (d == -32) {
					d = _getch();
					if (d == 72 || d == 75) {
						counter--;
						break;
					}
					else if (d == 80 || d == 77) {
						counter++;
						break;
					}
				}
			}
			goto M;
			break;
		case 3:
			c(4); button(99, 25, 14, "");
			for (int j = 0;;) {
				d = _getch();
				if (d == -32) {
					d = _getch();
					if (d == 72 || d == 75) {
						counter--;
						break;
					}
					else if (d == 80 || d == 77) {
						counter = 0;
						break;
					}
				}
			}
			goto M;
			break;
		}
	}*/
	
	
	
	
	
	gotoxy(81, 3); getline(cin, search); // eto galing sa project || goods na gumagana
	ifstream Record("Book_Record.txt");
	if (Record.is_open()) {
		string title, author, availability, year, location, callno;
		while (getline(Record, title)) {
			getline(Record, author);
			getline(Record, availability);
			getline(Record, year);
			getline(Record, location);
			getline(Record, callno);
			if (title == search || author == search) {
				gotoxy(6, 12); cout << title << endl;
				gotoxy(28, 12); cout << author << endl;
				gotoxy(68, 12); cout << availability << endl;
				gotoxy(55, 12); cout << year << endl;
				gotoxy(76, 12); cout << location << endl;
				gotoxy(99, 12); cout << callno << endl;
				print = true;
			}
		}
		Record.close();
	}
	else {
		cout << "Unable to open file!" << endl;
	}
	if (!print) {
		cout << "Book not found" << endl;
	}
	

	
	
	
	
	
	
	
	
	
	gotoxy(0, 29);	system("pause");
}

	
