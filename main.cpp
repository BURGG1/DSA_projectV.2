#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h>
#include <gotoxy.h> // ibahin nalang po to
#include <algorithm>
using namespace std;

#define gotoxy coorxy // alisin nalang din po to 

struct Book {
	string title, author, year, availability, location, isbn;
	struct Book* next;
};

void c(int c) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void button(int x, int y, int l, const string& a)//unang parameter x coord, syempre sunod yung y coord, yung l kung gaanon kalaki yung button, last is yung pangalan
{
	gotoxy(x, y); cout << char(201) << string(l, char(205)) << char(187); // top
	gotoxy(x, y + 1); cout << char(186); coorxy(x + l + 1, y + 1); cout << char(186);// two hori 
	gotoxy(x, y + 2); cout << char(200) << string(l, char(205)) << char(188);// bottom

	if (a.length() >= 6 && l >= 15) {
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

int getter(string s) {
	char a;
	char getter[32];
	for (int j = 0;;) {
		a = _getch();
		if (a == -32) {
			a = _getch();
			if (a == 72 || a == 75) {
				return 10;
				break;
			}
			else if (a == 80 || a == 77) {
				return 11;
				break;
			}
		}
		else if (a == 8 && j >= 1) {
			cout << "\b \b";
			getter[--j] = '\0';
		}
		else if ((a >= 'A' && a <= 'Z') || (a >= 'a' && a <= 'z') || (a == 32 && j < 32)) {
		    cout << a;
			getter[j] = a;
			++j;
		}
		else if (a == 13) {
			getter[j] = '\0';
			s = string(getter);
			return 10;
		}
	}
}


bool compare(const Book a, const Book b) { // SORTING CONDITION pwede pa dito mag add if want by category
	return a.title < b.title;
}

void sorting() { //SOTING FUNCTIONN

	Book book;
	vector<Book> catalog;
	ifstream Record("T_Book_Record.txt");
	if (Record.is_open()) {
		string line;
		while (getline(Record, line)) {
			stringstream ss(line);
			getline(ss, book.title, '\t');
			getline(ss, book.author, '\t');
			getline(ss, book.year, '\t');
			getline(ss, book.availability, '\t');
			getline(ss, book.location, '\t');
			getline(ss, book.isbn, '\t');
			if (!book.title.empty() && !book.author.empty() && !book.availability.empty() && !book.year.empty() && !book.location.empty() && !book.isbn.empty()) {
				catalog.push_back(book); 
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

		gotoxy(5, 12 + z); cout << string(20, ' ');
		gotoxy(28, 12 + z); cout << string(20, ' ');
		gotoxy(52, 12 + z); cout << string(8, ' ');
		gotoxy(67, 12 + z); cout << string(4, ' '); // erasing display lang sa table
		gotoxy(82, 12 + z); cout << string(13, ' ');
		gotoxy(102, 12 + z); cout << string(15, ' ');

		gotoxy(5, 12 + z); cout << book.title;
		gotoxy(28, 12 + z); cout << book.author;
		gotoxy(52, 12 + z); cout << book.availability;
		gotoxy(67, 12 + z); cout << book.year;
		gotoxy(82, 12 + z);	cout << book.location;
		gotoxy(102, 12 + z); cout << book.isbn;
		z++;
	}

}

void edit(string s) { // not yet done ARROW KEY TAPOS FLOW (baka di pa magamit) HAHAHAHAHA

	int ecount = 1, ecounter = 1;
	string title, author, availability, year, location, callno;
	string ntitle, nauthor, navailability, nyear, nlocation, ncallno;

	fstream Record("T_Book_Record.txt", ios::out | ios::in);
	string line;
	int y = 0;
	if (Record.is_open()) {

		while (getline(Record, line)) {
			stringstream ss(line);
			getline(ss, title, '\t');
			getline(ss, author, '\t');
			getline(ss, availability, '\t');
			getline(ss, year, '\t');
			getline(ss, location, '\t');
			getline(ss, callno, '\t');

			if (title == s) {
				gotoxy(5, 12); cout << title;
				gotoxy(28, 12); cout << author;
				gotoxy(52, 12); cout << availability;
				gotoxy(67, 12); cout << year;
				gotoxy(82, 12); cout << location;
				gotoxy(102, 12); cout << callno;
			}
		}
		Record.close();
	}
	else {
		gotoxy(80, 5); cout << "Unable to open file!" << endl;
		Sleep(500);
		gotoxy(80, 5); cout << string(25, ' ');
	}



confi:
	gotoxy(1, 1); cout << "Are you sure do you want to update this information?";
	//cin >> ecount;
	c(7); button(1, 3, 10, "yes");
	c(7); button(15, 3, 10, "no");

	if (ecount == 1) {
		c(4); button(1, 3, 10, "");
	}
	else if (ecount == 2) {
		c(4); button(15, 3, 10, "");
	}

	switch (_getch()) {
	case 224:
		switch (_getch()) {
		case 72:case 77:
			if (ecount < 1) { ecount = 2; }
			else ecount--;
			break;
		case 80:case 75:
			if (ecount > 2) { ecount = 1; }
			else ecount++;
			break;
		}
		goto confi;
		break;
	case 13: 
		switch (ecount) {
		case 1:
			int b;

		s:

			switch (ecounter) {
			case 1:
				gotoxy(5, 12); b = getter(ntitle);
				gotoxy(5, 12); cout << string(20, ' ');
				gotoxy(5, 12); cout << ntitle;
				if (b == 10) {
					if (ecounter < 1) ecount = 6;
					else ecounter--;
				}
				else ecounter++;
				goto s;
				break;
			case 2:
				gotoxy(28, 12); b = getter(nauthor);
				gotoxy(28, 12); cout << string(20, ' ');
				gotoxy(28, 12); cout << ntitle;
				if (b == 10) ecounter--;
				else ecounter++;
				goto s;
				break;
			case 3:
				gotoxy(52, 12); b = getter(navailability);
				gotoxy(52, 12); cout << string(8, ' ');
				gotoxy(52, 12); cout << ntitle;
				if (b == 10) ecounter--;
				else ecounter++;
				goto s;
				break;
			case 4:
				gotoxy(67, 12); b = getter(nyear);
				gotoxy(67, 12); cout << string(4, ' ');
				gotoxy(67, 12); cout << ntitle;
				if (b == 10) ecounter--;
				else ecounter++;
				goto s;
				break;
			case 5:
				gotoxy(82, 12); b = getter(nlocation);
				gotoxy(82, 12); cout << string(13, ' ');
				gotoxy(82, 12); cout << ntitle;
				if (b == 10) ecounter--;
				else ecounter++;
				goto s;
				break;
			case 6:
				gotoxy(102, 12); b = getter(ncallno);
				gotoxy(102, 12); cout << string(16, ' ');
				gotoxy(102, 12); cout << ntitle;
				if (b == 10) ecounter--;
				else ecounter = 1;
				goto s;
				break;
			case 7:

				/*ofstream Record;
				Record.open("T_Book_Record.txt", ios::out);
				if (Record.is_open()) {
					Record <<
				}*/

				cout << ntitle;
				cout << nauthor;
				cout << navailability;
				cout << nyear;
				cout << nlocation;
				cout << ncallno;

				break;
			}

			break;
		case 2:
			cout << "Ayaw gumana bes";
			break;
		}



	
	}
}



//int main() { // ADD (SUCCESSFULL)
//
//	Book b;
//	int ct = 2;
//	Book* first = NULL;
//
//	table(10, 1, 1);
//start:
//
//	gotoxy(5, 12); getline(cin, b.title);
//	gotoxy(28, 12); getline(cin, b.author);
//	gotoxy(52, 12); getline(cin, b.availability);
//	gotoxy(67, 12); getline(cin, b.year);
//	gotoxy(82, 12); getline(cin, b.location);
//	gotoxy(100, 12); getline(cin, b.isbn);
//
//	Book* tstore = new Book;
//	tstore->title = b.title;
//	tstore->author = b.author;
//	tstore->availability = b.availability;
//	tstore->year = b.year;
//	tstore->location = b.location;
//	tstore->isbn = b.isbn;
//	tstore->next = NULL;
//
//	Book* tstore2;
//	if (first == NULL) {
//		first = tstore;
//	}
//	else {
//		tstore2 = first;
//		while (tstore2->next) tstore2 = tstore2->next;;
//		tstore2 = tstore;
//	}
//	Book* save = first;
//	ofstream Record;
//	Record.open("T_Book_Record.txt" , ios :: out | ios :: app);
//	if (Record.is_open()) {
//		gotoxy(45, 3); cout << "Book Successfully Added!";
//		while (save) {
//			Record << save->title << '\t' << save->author << '\t' << save->availability << '\t'
//			<< save->year << '\t' << save->location << '\t' << save->isbn << endl;
//			save = save->next;
//		}
//	}
//	else {
//		gotoxy(45, 3); cout << "Unable to add Book!";
//	}
//	Record.close();
//}


int main() { // Book Record Layout || MANAGE
	string search;
	table(10, 1, 1);
	

	gotoxy(1, 1); getline(cin, search);
 	edit(search);

	
}


//int main() { // *SUCCESSFUL! might use if trip nyo  (SEARCH!)
//
//	char d;
//	int counter = 0;
//	char searchbook[32];
//	string search , tempTitle;
//	bool print = false;
//M:
//	gotoxy(70, 2); cout << char(218) << string(37, char(196)) << char(191);
//	gotoxy(70, 3); cout << char(179); gotoxy(71, 3); cout << "Search:" << char(179); gotoxy(108, 3); cout << char(179); // search bar
//	gotoxy(70, 4); cout << char(192) << string(37, char(196)) << char(217);
//
//	table(10, 1, 1);
//	
//	/*c(7); button(60, 25, 15, "Delete");
//	c(7); button(80, 25, 14, "Edit");*/
//	c(7); button(99, 25, 14, "Back");
//	gotoxy(80, 3); cout << string(15, ' ');
//
//
//	for (int i = 0;;) {
//
//		switch (counter) {
//		case 0:
//
//			gotoxy(80, 3);
//			for (int j = 0;;) {
//				d = _getch();
//				if (d == -32) {
//					d = _getch();
//					if (d == 72 || d == 75) {
//						counter = 1;
//						break;
//					}
//					else if (d == 80 || d == 77) {
//						counter++;
//						break;
//					}
//				}
//				else if (d == 8 && j >= 1) {
//					cout << "\b \b";
//					searchbook[--j] = '\0';
//				}
//				else if ((d >= 'A' && d <= 'Z') || (d >= 'a' && d <= 'z') || (d == 32 && j < 32)) {
//					coorxy(80 + j, 3); cout << d;
//					searchbook[j] = d;
//					++j;
//				}
//				else if (d == 13) {
//					searchbook[j] = '\0';
//					search = string(searchbook);
//
//					Book book;
//
//					ifstream Record("T_Book_Record.txt");
//					string title, author, availability, year, location, callno;
//					string line;
//					int y = 0;
//					if (Record.is_open()) {
//						bool found = false; // Flag to if found
//
//						for (int y = 0; y < 5; y++){
//							gotoxy(6, 12 + y); cout << string(20, ' ');
//							gotoxy(28, 12 + y); cout << string(20, ' ');
//							gotoxy(52, 12 + y); cout << string(8, ' ');
//							gotoxy(67, 12 + y); cout << string(4, ' '); // erasing display lang sa table
//							gotoxy(82, 12 + y); cout << string(13, ' ');
//							gotoxy(102, 12 + y); cout << string(15, ' ');
//						}
//
//						while (getline(Record, line)) {
//							stringstream ss(line);
//							getline(ss, title, '\t');
//							getline(ss, author, '\t');
//							getline(ss, availability, '\t');
//							getline(ss, year, '\t');
//							getline(ss, location, '\t');
//							getline(ss, callno, '\t');
//
//							if (title == search || author == search) {
//
//								found = true;
//								gotoxy(5, 12 + y); cout << title;
//								gotoxy(28, 12 + y); cout << author;
//								gotoxy(52, 12 + y); cout << availability;
//								gotoxy(67, 12 + y); cout << year;
//								gotoxy(82, 12 + y); cout << location;
//								gotoxy(102, 12 + y); cout << callno;
//								y++;
//
//							}
//						     tempTitle = title;
//
//						}
//						Record.close();
//
//						if (!found) {
//							gotoxy(80, 5); cout << "No results found." << endl; // Inform user if not found
//							Sleep(500);
//							gotoxy(80, 5); cout << string(25, ' ');
//						}
//					}
//					else {
//							gotoxy(80, 5); cout << "Unable to open file!" << endl;
//							Sleep(500);
//							gotoxy(80, 5); cout << string(25, ' ');
//					}
//					break;
//				}
//			}
//			goto M;
//			break;
//		case 1:
//			c(4); button(99, 25, 14, ""); // BACK
//			for (int i = 0;;) {
//				d = _getch();
//				if (d == -32) {
//					d = _getch();
//					if (d == 72 || d == 75) {
//						counter--;
//						break;
//					}
//					else if (d == 80 || d == 77) {
//						counter = 0;
//						break;
//					}
//				}
//			}
//			goto M;
//			break;
//		}
//	}
//	gotoxy(0, 29);	system("pause");
//
//}

//int main() // ViEW ALL and SORING done(di ko sure kung tama)
//{
//	
//    int counter = 1;
//	char d;
//
//	gotoxy(45, 2); cout << "ALL BOOKS!";
//
//	table(10, 1, 1);
//	string title, author, year, availability, location, callno;
//	
//
//	ifstream Record("T_Book_Record.txt");
//	if (Record.is_open()) {
//		string line;
//		int y = 0;
//		while (getline(Record, line)) {
//			stringstream ss(line);
//			getline(ss, title, '\t');
//			getline(ss, author, '\t');
//			getline(ss, year, '\t');
//			getline(ss, availability, '\t');
//			getline(ss, location, '\t');
//			getline(ss, callno, '\t');
//			
//			gotoxy(5, 12 + y); cout << title;
//			gotoxy(28, 12 + y); cout << author;
//			gotoxy(67, 12 + y); cout << availability;
//			gotoxy(52, 12 + y); cout << year;
//			gotoxy(82, 12 + y); cout << location;
//			gotoxy(102, 12 + y); cout << callno;
//			y++;
//		}
//		Record.close();
//	}
//	else {
//		cout << "Unable to open file!" << endl;
//	}
//m:
//	c(7); button(4, 5, 14, "A-Z");
//	c(7); button(99, 25, 14, "Back");
//
//	if (counter == 1){
//		c(4); button(4, 5, 14, "");
//	}
//	else if (counter == 2) {
//		c(4); button(99, 25, 14, "");
//	}
//
//	switch (_getch()) {
//	case 224:
//		switch (_getch()) {
//		case 72:case 75:
//			if (counter <= 1) {
//				counter = 2;
//			}
//			else counter--;
//			break;
//		case 80:case 77:
//			if (counter >= 2)
//			{
//				counter = 1;
//			}
//			else counter++;
//			break;
//		}
//		goto m;
//		break;
//	case 13:
//		switch (counter) {
//		case 1:
//			sorting();
//			goto m;
//			break;
//		}
//	case 2:
//		
//		exit(0);
//		break;
//	}
//
//	gotoxy(1, 29); system("pause");
//}

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
