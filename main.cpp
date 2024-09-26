#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h>
#include <gotoxy.h> // ibahin nalang din if di nagana
#include <algorithm>
using namespace std;
#include "UI_pack.h"
#define gotoxy coorxy //alisin nyo na to sakin lang merong coorxy na function

//int main() { // *SUCCESSFUL! might use if trip nyo
//
//	char d;
//	int counter = 0;
//	char searchbook[32];
//	string search;
//	bool print = false; 
//M:
//	gotoxy(70, 2); cout << char(218) << string(37, char(196)) << char(191);
//	gotoxy(70, 3); cout << char(179); gotoxy(71, 3); cout << "Search:" << char(179); gotoxy(108, 3); cout << char(179); // search bar
//	gotoxy(70, 4); cout << char(192) << string(37, char(196)) << char(217);
//
//	table(10, 1, 1);
//	
//	c(7); button(60, 25, 15, "Delete");
//	c(7); button(80, 25, 14, "Edit");
//	c(7); button(99, 25, 14, "Back");
//	gotoxy(80, 3); cout << string(15, ' ');
//
//
//		for (int i = 0;;) {
//
//			switch (counter) {
//			case 0:
//				gotoxy(80, 3);
//				for (int j = 0;;) {
//					d = _getch();
//					if (d == -32) {
//						d = _getch();
//						if (d == 72 || d == 75) {
//							counter = 3;
//							break;
//						}
//						else if (d == 80 || d == 77) {
//							counter++;
//							break;
//						}
//					}
//					else if (d == 8 && j >= 1) {
//						cout << "\b \b";
//						searchbook[--j] = '\0';
//					}
//					else if ((d >= 'A' && d <= 'Z') || (d >= 'a' && d <= 'z') || (d == 32 && j < 32)) {
//						coorxy(80 + j, 3); cout << d;
//						searchbook[j] = d;
//						++j;
//					}
//					else if (d == 13) {
//						searchbook[j] = '\0';
//						search = string(searchbook);
//
//						ifstream Record("TryBook_Record.txt");
//						string title, author, availability, year, location, callno;
//						string line;
//
//						if (Record.is_open()) {
//							bool found = false; // Flag to if found
//							while (getline(Record, line)) {
//								stringstream ss(line);
//								getline(ss, title, '\t');
//								getline(ss, author, '\t');
//								getline(ss, availability, '\t');
//								getline(ss, year, '\t');
//								getline(ss, location, '\t');
//								getline(ss, callno, '\t');
//
//								if (title == search || author == search) {
//
//									gotoxy(6, 12); cout << string(15, ' ');
//									gotoxy(28, 12); cout << string(20, ' ');
//									gotoxy(52, 12); cout << string(8, ' ');
//									gotoxy(67, 12); cout << string(4, ' '); // erasing display lang sa table
//									gotoxy(82, 12); cout << string(15, ' ');
//									gotoxy(102, 12); cout << string(20, ' ');
//
//									found = true;
//									gotoxy(6, 12); cout << title;
//									gotoxy(28, 12); cout << author;
//									gotoxy(52, 12); cout << availability;
//									gotoxy(67, 12); cout << year;
//									gotoxy(82, 12); cout << location;
//									gotoxy(102, 12); cout << callno;
//								}
//							}
//							Record.close();
//
//							if (!found) {
//								cout << "No results found." << endl; // Inform user if not found
//							}
//						}
//						else {
//							if (!print) {
//								cout << "Unable to open file!" << endl;
//							}
//						}
//						break;
//					}
//				}
//				goto M;
//				break;
//			case 1:
//				c(4); button(60, 25, 15, ""); // DELETE 
//				goto M;
//				break;
//			case 2:
//				c(4); button(80, 25, 14, ""); // UPDATE
//				goto M;
//				break;
//			case 3:
//				c(4); button(99, 25, 14, ""); // BACK
//				goto M;
//				break;
//			}
//		}
//	gotoxy(0, 29);	system("pause");
//	
//}

struct Book { 
	string title, author, year, availability, location, callno;
};

bool compare(const Book a, const Book b) { // SORTING TO CONDITION
	return a.title < b.title;
}

void sorting(){ //SOTING FUNCTIONN

	Book book;
	vector<Book> catalog;
	ifstream Record("TryBook_Record.txt");
	if (Record.is_open()) {
		string line;
		while (getline(Record, line)) {
			stringstream ss(line);
			getline(ss, book.title, '\t');
			getline(ss, book.author, '\t');
			getline(ss, book.year, '\t');
			getline(ss, book.availability, '\t');
			getline(ss, book.location, '\t');
			getline(ss, book.callno, '\t');
			if (!book.title.empty() && !book.author.empty() && !book.availability.empty() && !book.year.empty() && !book.location.empty() && !book.callno.empty()) {
				catalog.push_back(book); // for sorting pushback the variable sa isang variable
			}
		}
		Record.close();
	}
	else {
		cout << "Unable to open the file";
	}
	
	sort(catalog.begin(), catalog.end(), compare); // dito nya isosort
	int z = 0;
	for (const auto& book : catalog) {

		gotoxy(6, 12 + z); cout << string(15, ' ');
		gotoxy(28, 12 + z); cout << string(20, ' ');
	    gotoxy(52, 12 + z); cout << string(8, ' ');
		gotoxy(67, 12 + z); cout << string(4, ' '); // erasing display lang sa table
		gotoxy(82, 12 + z); cout << string(13, ' ');
		gotoxy(102, 12 + z); cout << string(15, ' ');

		gotoxy(6, 12 + z); cout << book.title;
		gotoxy(28, 12 + z); cout << book.author;
		gotoxy(52, 12 + z); cout << book.availability;
		gotoxy(67, 12 + z); cout << book.year;
		gotoxy(82, 12 + z);	cout << book.location;
		gotoxy(102, 12 + z); cout << book.callno;
		z++;
	}

}

int main() // ViEW ALL and SORING done(di ko sure kung tama)
{
	
    int counter = 1;
	char d;

	gotoxy(45, 2); cout << "ALL BOOKS!";

	table(10, 1, 1);
	string title, author, year, availability, location, callno;
	

	ifstream Record("TryBook_Record.txt");
	if (Record.is_open()) {
		string line;
		int y = 0;
		while (getline(Record, line)) {
			stringstream ss(line);
			getline(ss, title, '\t');
			getline(ss, author, '\t');
			getline(ss, year, '\t');
			getline(ss, availability, '\t');
			getline(ss, location, '\t');
			getline(ss, callno, '\t');
			
			gotoxy(6, 12 + y); cout << title;
			gotoxy(28, 12 + y); cout << author;
			gotoxy(67, 12 + y); cout << availability;
			gotoxy(52, 12 + y); cout << year;
			gotoxy(82, 12 + y); cout << location;
			gotoxy(102, 12 + y); cout << callno;
			y++;
		}
		Record.close();
	}
	else {
		cout << "Unable to open file!" << endl;
	}
m:
	c(7); button(4, 5, 14, "A-Z");
	c(7); button(99, 25, 14, "Back");

	if (counter == 1){
		c(4); button(4, 5, 14, "");
	}
	else if (counter == 2) {
		c(4); button(99, 25, 14, "");
	}

	switch (_getch()) {
	case 224:
		switch (_getch()) {
		case 72:case 75:
			if (counter <= 1) {
				counter = 2;
			}
			else counter--;
			break;
		case 80:case 77:
			if (counter >= 2)
			{
				counter = 1;
			}
			else counter++;
			break;
		}
		goto m;
		break;
	case 13:
		switch (counter) {
		case 1:
			sorting();
			goto m;
			break;
		}
	case 2:
		
		exit(0);
		break;
	}

	gotoxy(1, 29); system("pause");
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