#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h>
#include <gotoxy.h> // ibahin nalang din if di nagana
#include <algorithm>
using namespace std;

#define gotoxy coorxy // alis nalang to

const int MAX = 30;

struct Book {
	string title, author, year, availability, location, isbn;
	struct Book* next;
};

vector<string> getSuggestions(const vector<string>& suggestions, const string& input) {
	vector<string> filteredSuggestions;
	for (const auto& suggestion : suggestions) {
		if (suggestion.find(input) == 0) { // Check if the suggestion starts with the input
			filteredSuggestions.push_back(suggestion);
		}
	}
	return filteredSuggestions;
}

void c(int c) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void hc(int x) {
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

void button(int x, int y, int l, const string& a, int p)//unang parameter x coord, syempre sunod yung y coord, yung l kung gaanon kalaki yung button, last is yung pangalan
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
	if (p == 1) {
		while (_getch() != 13);
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

int getter(string& s) { // pang get ng value
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
		else if ((a >= 'A' && a <= 'Z') || (a >= 'a' && a <= 'z') || (a >= '0' && a <= '9') || (a == 32 && j < 32)) {
			cout << a;
			getter[j] = a;
			++j;
		}
		else if (a == 13) {
			getter[j] = '\0';
			s = string(getter);
			return 11;
		}
	}
}

void search() { // goods na (SEARCH!)

	table(3, 1, 1);
	char d;
	string title, author, availability, year, location, isbn;
	int counter = 0, y = 0;
	string searchbook;
	string search, line;
	vector<string> sug;
	ifstream Record("Book_Record.txt");
	if (Record.is_open()) {
		while (getline(Record, line)) {
			stringstream ss(line);
			getline(ss, title, '\t');
			getline(ss, author, '\t');
			getline(ss, availability, '\t');
			getline(ss, year, '\t');
			getline(ss, location, '\t');
			getline(ss, isbn, '\t');
			sug.push_back(title);  // Store titles
			sug.push_back(author);  // Store authors
			sug.push_back(isbn); // Store isbn
		}
		Record.close();
	}


M: 
	gotoxy(70, 2); cout << char(218) << string(37, char(196)) << char(191);
	gotoxy(70, 3); cout << char(179);
	gotoxy(71, 3); cout << "Search:" << char(179);
	gotoxy(108, 3); cout << char(179);
	gotoxy(70, 4); cout << char(192) << string(37, char(196)) << char(217);
	gotoxy(80, 3); cout << string(15, ' '); // Clear previous input
	c(7); button(100, 5, 14, "Back", 0); // BACK

	switch (counter) {
	case 0:
		hc(0);
		gotoxy(80, 3);
		for (int j = 0;;) {
			d = _getch();
			if (d == -32) {
				d = _getch();
				if (d == 72 || d == 75) {
					counter = 1;
					break;
				}
				else if (d == 80 || d == 77) {
					counter++;
					break;
				}
			}
			else if (d == 8 && j > 0) { // Backspace
				gotoxy(80 + j, 3); cout << "\b \b";
				searchbook.pop_back();
				--j;
				for (int i = 0; i < 4; i++) {
					gotoxy(80, 5 + i);
					cout << string(20, ' '); // Clear previous suggestions
				}
				gotoxy(80 + j, 3);
			}
			else if ((d >= 'a' && d <= 'z') || (d >= 'A' && d <= 'Z') || (d == ' ' && j < 32)) {
				int x = 0;
				gotoxy(80 + j, 3); cout << d;
				searchbook += d;
				++j;
				auto filtered = getSuggestions(sug, searchbook);

				for (x = 0; x < 4; ++x) {
					gotoxy(80, 5 + x);
					cout << string(20, ' '); // Clear suggestion area
				}
				x = 0; // Reset x for displaying suggestions
				for (const auto& suggestion : filtered) {
					gotoxy(80, 5 + x);
					cout << suggestion; // Display suggestion
					x++;
				}
				gotoxy(80 + j, 3);
			}
			else if (d == 13) { // Enter key
				for (int x = 0; x < 5; ++x) {
					gotoxy(80, 5 + x);
					cout << string(20, ' '); // Clear suggestion area
				}
				search = searchbook;
				ifstream records("Book_Record.txt");
				if (records.is_open()) {
					bool found = false;
					for (int i = 0; i < y; i++) {
						gotoxy(5, 12 + i); cout << string(15, ' ');
						gotoxy(28, 12 + i); cout << string(15, ' ');
						gotoxy(52, 12 + i); cout << string(8, ' ');
						gotoxy(67, 12 + i); cout << string(4, ' '); // erasing display lang sa table
						gotoxy(82, 12 + i); cout << string(13, ' ');
						gotoxy(102, 12 + i); cout << string(15, ' ');
					}
					while (getline(records, line)) {
						stringstream ss(line);
						getline(ss, title, '\t');
						getline(ss, author, '\t');
						getline(ss, availability, '\t');
						getline(ss, year, '\t');
						getline(ss, location, '\t');
						getline(ss, isbn, '\t');
						if (title == search || author == search || isbn == search) {
							found = true;
							gotoxy(5, 12 + y); cout << title;
							gotoxy(28, 12 + y); cout << author;
							gotoxy(52, 12 + y); cout << availability;
							gotoxy(67, 12 + y); cout << year;
							gotoxy(82, 12 + y); cout << location;
							gotoxy(102, 12 + y); cout << isbn;
							y++;
						}
					}
					sug.clear();
					sug.shrink_to_fit();
					searchbook = "";
					records.close();
					if (!found) {
						gotoxy(10, 5); c(4); cout << "No results found."; c(7);
						Sleep(500);
						gotoxy(10, 5); cout << string(25, ' '); // Clear message
					}
				}
				else {
					gotoxy(80, 5); cout << "Unable to open file!";
					Sleep(500);
					gotoxy(80, 5); cout << string(25, ' ');
				}
				break;
			}
		}
		goto M;
		break;
	case 1:
		hc(1);
		c(4); button(100, 5, 14, "", 0); // BACK
		switch (_getch()) {
		case 224:
			switch (_getch()) {
			case 72: case 75:
				counter--;
				break;
			case 80: case 77:
				counter = 0;
				break;
			}
			goto M;
			break;
		case 13:
			return;
			break;
		}
		hc(0);
		break;
	}
	return;
}
	

bool add(int p, int size) { // ADD (SUCCESSFULL)

	ofstream Record;
	Book book; Book* tstore; Book* save; Book* tstore2; //for linked list storage
	Book* first = NULL;
	int kcounter = 1;
	int b, h = 3;
	int y = p;
	for (int i = 1; i < 10; i++) {
		gotoxy(1, i); cout << string(119, ' ');
	}

	gotoxy(45, 1); cout << "ADD BOOK";
	table(h + y, 1, 1);
	for (int i = 0; i < y; i++) {
		gotoxy(4, 12 + y); cout << string(21, ' ');
		gotoxy(26, 12 + y); cout << string(24, ' ');
		gotoxy(51, 12 + y); cout << string(14, ' '); //pang erase sa extra lines
		gotoxy(66, 12 + y); cout << string(8, ' ');
		gotoxy(75, 12 + y); cout << string(21, ' ');
		gotoxy(97, 12 + y); cout << string(20, ' ');
	}

a:
	if (size != MAX) {

		if (y == 0) { // unang add
		f:
			hc(0);
			c(7); button(60, 5, 15, "Confirm", 0);
			c(7); button(80, 5, 15, "Back", 0);
			switch (kcounter) {
			case 1:
				gotoxy(5, 12); b = getter(book.title);
				gotoxy(5, 12); cout << string(20, ' ');
				gotoxy(5, 12 + y); cout << book.title;
				if (b == 10) {
					if (kcounter <= 1) {
						kcounter = 8;
					}
					else kcounter--;
				}
				else kcounter++;
				goto f;
				break;
			case 2:
				gotoxy(28, 12); b = getter(book.author);
				gotoxy(28, 12); cout << string(20, ' ');
				gotoxy(28, 12); cout << book.author;
				if (b == 10) kcounter--;
				else kcounter++;
				goto f;
				break;
			case 3:
				gotoxy(52, 12); b = getter(book.availability);
				gotoxy(52, 12); cout << string(8, ' ');
				gotoxy(52, 12); cout << book.availability;
				if (b == 10) kcounter--;
				else kcounter++;
				goto f;
				break;
			case 4:
				gotoxy(67, 12); b = getter(book.year);
				gotoxy(67, 12); cout << string(4, ' ');
				gotoxy(67, 12); cout << book.year;
				if (b == 10) kcounter--;
				else kcounter++;
				goto f;
				break;
			case 5:
				gotoxy(82, 12); b = getter(book.location);
				gotoxy(82, 12); cout << string(13, ' ');
				gotoxy(82, 12); cout << book.location;
				if (b == 10) kcounter--;
				else kcounter++;
				goto f;
				break;
			case 6:
				gotoxy(102, 12); b = getter(book.isbn);
				gotoxy(102, 12); cout << string(13, ' ');
				gotoxy(102, 12); cout << book.isbn;
				if (b == 10) kcounter--;
				else kcounter++;
				goto f;
				break;
			case 7: // confirm
				hc(1);
				c(4); button(60, 5, 15, "", 0); c(7); // edit
				switch (_getch()) {
				case 224:
					switch (_getch()) {
					case 72:case 75:
						kcounter--;
						break;
					case 80:case 77:
						kcounter++;
						break;
					}
					goto f;
					break;
				case 13:
					if (book.title == "" || book.author == "" || book.availability == "" || book.year == "" || book.location == "" || book.isbn == "") {
						c(4); gotoxy(30, 1); cout << "information must be complete to add a book please try again!"; c(7);
						for (int y = 0; y < 5; y++) {
							gotoxy(6, 12 + y); cout << string(20, ' ');
							gotoxy(28, 12 + y); cout << string(20, ' ');
							gotoxy(52, 12 + y); cout << string(8, ' ');
							gotoxy(67, 12 + y); cout << string(4, ' '); // erasing display lang sa table
							gotoxy(82, 12 + y); cout << string(13, ' ');
							gotoxy(102, 12 + y); cout << string(15, ' ');
						}
						book.title = "", book.author = "", book.availability = "", book.year = "", book.location = "", book.isbn = ""; //para maerase din yung laman
						kcounter = 1;
						goto f;
					}
					else {
						tstore = new Book;
						tstore->title = book.title;
						tstore->author = book.author;
						tstore->availability = book.availability;
						tstore->year = book.year;
						tstore->location = book.location;
						tstore->isbn = book.isbn;
						tstore->next = NULL;


						if (first == NULL) {
							first = tstore;
						}
						else {
							tstore2 = first;
							while (tstore2->next) tstore2 = tstore2->next;;
							tstore2 = tstore;
						}

						save = first;
						Record.open("Book_Record.txt", ios::out | ios::app);
						if (Record.is_open()) {
							gotoxy(45, 8); c(4); cout << "Book Successfully Added!"; c(7);
							Sleep(1000);
							gotoxy(45, 8); cout << string(30, ' ');
							while (save) {
								Record << save->title << '\t' << save->author << '\t' << save->availability << '\t'
									<< save->year << '\t' << save->location << '\t' << save->isbn << endl;
								save = save->next;
							}
						}
						else {
							gotoxy(45, 3); cout << "Unable to add Book!";
						}
						Record.close();
					}
					break;
				}
				return true;
				break;
			case 8:
				hc(1);
				c(4); button(80, 5, 15, "", 0); c(7);// back
				switch (_getch()) {
				case 224:
					switch (_getch()) {
					case 72:case 75:
						kcounter--;
						break;
					case 80:case 77:
						kcounter = 1;
						break;
					}
					goto f;
					break;
				case 13:
					return false;
					break;
				}
				goto f;
				break;
			}
		}
		else {// the rest;
		s:
		hc(0);
			c(7); button(60, 5, 15, "Confirm", 0);
			c(7); button(80, 5, 15, "Back", 0);
			switch (kcounter) {
			case 1:
				gotoxy(5, 12 + y); b = getter(book.title);
				gotoxy(5, 12 + y); cout << string(20, ' ');
				gotoxy(5, 12 + y); cout << book.title;
				if (b == 10) {
					if (kcounter <= 1) {
						kcounter = 8;
					}
					else kcounter--;
				}
				else kcounter++;
				goto s;
				break;
			case 2:
				gotoxy(28, 12 + y); b = getter(book.author);
				gotoxy(28, 12 + y); cout << string(20, ' ');
				gotoxy(28, 12 + y); cout << book.author;
				if (b == 10) kcounter--;
				else kcounter++;
				goto s;
				break;
			case 3:
				gotoxy(52, 12 + y); b = getter(book.availability);
				gotoxy(52, 12 + y); cout << string(8, ' ');
				gotoxy(52, 12 + y); cout << book.availability;
				if (b == 10) kcounter--;
				else kcounter++;
				goto s;
				break;
			case 4:
				gotoxy(67, 12 + y); b = getter(book.year);
				gotoxy(67, 12 + y); cout << string(4, ' ');
				gotoxy(67, 12 + y); cout << book.year;
				if (b == 10) kcounter--;
				else kcounter++;
				goto s;
				break;
			case 5:
				gotoxy(82, 12 + y); b = getter(book.location);
				gotoxy(82, 12 + y); cout << string(13, ' ');
				gotoxy(82, 12 + y); cout << book.location;
				if (b == 10) kcounter--;
				else kcounter++;
				goto s;
				break;
			case 6:
				gotoxy(102, 12 + y); b = getter(book.isbn);
				gotoxy(102, 12 + y); cout << string(13, ' ');
				gotoxy(102, 12 + y); cout << book.isbn;
				if (b == 10) kcounter--;
				else kcounter++;
				goto s;
				break;
			case 7: // confirm
				hc(1);
				c(4); button(60, 5, 15, "", 0); c(7); // edit
				switch (_getch()) {
				case 224:
					switch (_getch()) {
					case 72:case 75:
						kcounter--;
						break;
					case 80:case 77:
						kcounter++;
						break;
					}
					goto s;
					break;
				case 13:
					if (book.title == "" || book.author == "" || book.availability == "" || book.year == "" || book.location == "" || book.isbn == "") {
						c(4); gotoxy(30, 1); cout << "information must be complete to add a book please try again!"; c(7);
						for (int y = 0; y < 5; y++) {
							gotoxy(6, 12 + y); cout << string(20, ' ');
							gotoxy(28, 12 + y); cout << string(20, ' ');
							gotoxy(52, 12 + y); cout << string(8, ' ');
							gotoxy(67, 12 + y); cout << string(4, ' '); // erasing display lang sa table
							gotoxy(82, 12 + y); cout << string(13, ' ');
							gotoxy(102, 12 + y); cout << string(15, ' ');
						}
						book.title = "", book.author = "", book.availability = "", book.year = "", book.location = "", book.isbn = ""; //para maerase din yung laman
						kcounter = 1;
						goto s;
					}
					else {
						tstore = new Book;
						tstore->title = book.title;
						tstore->author = book.author;
						tstore->availability = book.availability;
						tstore->year = book.year;
						tstore->location = book.location;
						tstore->isbn = book.isbn;
						tstore->next = NULL;


						if (first == NULL) {
							first = tstore;
						}
						else {
							tstore2 = first;
							while (tstore2->next) tstore2 = tstore2->next;;
							tstore2 = tstore;
						}

						save = first;
						Record.open("Book_Record.txt", ios::out | ios::app);
						if (Record.is_open()) {
							gotoxy(45, 8); c(4); cout << "Book Successfully Added!"; c(7);
							Sleep(1000);
							gotoxy(45, 8); cout << string(30, ' ');
							while (save) {
								Record << save->title << '\t' << save->author << '\t' << save->availability << '\t'
									<< save->year << '\t' << save->location << '\t' << save->isbn << endl;
								save = save->next;
							}
							Record.close();
						}
						else {
							gotoxy(45, 3); cout << "Unable to add Book!";
						}
					}
					break;
				}
				return true;
				break;
			case 8:
				hc(1);
				c(4); button(80, 5, 15, "", 0); c(7);// back
				switch (_getch()) {
				case 224:
					switch (_getch()) {
					case 72:case 75:
						kcounter--;
						break;
					case 80:case 77:
						kcounter = 1;
						break;
					}
					goto s;
					break;
				case 13:
					return false;
					break;
				}
				goto s;
				break;
			}

		}
	}
	else {
		gotoxy(45, 2); cout << "File Overflow";

	}
}

void edit(string s) { // goods na
	system("cls");
	gotoxy(45, 16);
	vector<Book>tempb;
	int ecount = 2, ecounter = 1;
	bool found = false;
	string title, author, availability, year, location, isbn;
	string ntitle = "", nauthor = "", navailability = "", nyear = "", nlocation = "", nisbn = "";

	table(3, 1, 1);
	
	fstream Record("Book_Record.txt", ios::in);
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
			getline(ss, isbn, '\t');
			if (title == s) {
				gotoxy(5, 12); cout << title;
				gotoxy(28, 12); cout << author;
				gotoxy(52, 12); cout << availability;
				gotoxy(67, 12); cout << year;
				gotoxy(82, 12); cout << location;
				gotoxy(102, 12); cout << isbn;
			}
			tempb.push_back({ title ,author, availability, year, location, isbn });
		}
		Record.close();
	}
	else {
		gotoxy(80, 5); cout << "Unable to open file!" << endl;
		Sleep(500);
		gotoxy(80, 5); cout << string(25, ' ');
	}

	for (auto& book : tempb) {

		if (book.title == s) {
			ntitle = book.title;
			nauthor = book.author;
			navailability = book.availability;
			nyear = book.year;
			nlocation = book.location;
			nisbn = book.isbn;
		}
	}
	gotoxy(38, 2); cout << "Are you sure do you want to update this information?";


confi:
	hc(1);
	c(7); button(45, 3, 10, "yes", 0);
	c(7); button(60, 3, 10, "no", 0);

	if (ecount == 1) {
		c(4); button(45, 3, 10, "", 0);
	}
	else if (ecount == 2) {
		c(4); button(60, 3, 10, "", 0);
	}

	switch (_getch()) {
	case 224:
		switch (_getch()) {
		case 72:case 75:
			if (ecount == 1) {
				ecount = 2;
			}
			else ecount--;
			break;
		case 80:case 77:
			if (ecount == 2) {
				ecount = 1;
			}
			else ecount++;
			break;
		}
		goto confi;
		break;
	case 13:
		hc(0);
		switch (ecount) {
		case 1: // pag yes
			int b;
			for (int i = 0; i < 5; i++) {
				gotoxy(5, 1 + i); cout << string(100, ' ');
			}
			table(3, 1, 7);
			gotoxy(45, 14); cout << "Input new information";

		s:
			hc(0);
			switch (ecounter) { // pang kuha ng value nagagalaw arrow key
			case 1:
				gotoxy(5, 18); b = getter(ntitle);
				gotoxy(5, 18); cout << string(20, ' ');
				gotoxy(5, 18); cout << ntitle;
				if (b == 10) {
					if (ecounter < 1) ecounter = 6;
					else ecounter--;
				}
				else ecounter++;
				goto s;
				break;
			case 2:
				gotoxy(28, 18); b = getter(nauthor);
				gotoxy(28, 18); cout << string(20, ' ');
				gotoxy(28, 18); cout << nauthor;
				if (b == 10) ecounter--;
				else ecounter++;
				goto s;
				break;
			case 3:
				gotoxy(52, 18); b = getter(navailability);
				gotoxy(52, 18); cout << string(8, ' ');
				gotoxy(52, 18); cout << navailability;
				if (b == 10) ecounter--;
				else ecounter++;
				goto s;
				break;
			case 4:
				gotoxy(67, 18); b = getter(nyear);
				gotoxy(67, 18); cout << string(4, ' ');
				gotoxy(67, 18); cout << nyear;
				if (b == 10) ecounter--;
				else ecounter++;
				goto s;
				break;
			case 5:
				gotoxy(82, 18); b = getter(nlocation);
				gotoxy(82, 18); cout << string(13, ' ');
				gotoxy(82, 18); cout << nlocation;
				if (b == 10) ecounter--;
				else ecounter++;
				goto s;
				break;
			case 6:
				gotoxy(102, 18); b = getter(nisbn);
				gotoxy(102, 18); cout << string(13, ' ');
				gotoxy(102, 18); cout << nisbn;
				if (b == 10) ecounter--;
				else ecounter++;
				goto s;
				break;
			case 7: // save
				int w = 2;
				gotoxy(30, 2); cout << "Save changes?";

			a:
				hc(1);
				c(7); button(20, 4, 15, "Save", 0);
				c(7); button(40, 4, 15, "Discard", 0);
				if (w == 1) {
					c(4); button(20, 4, 15, "Save", 0);
				}
				else if (w == 2) {
					c(4); button(40, 4, 15, "Discard", 0);
				}
				switch (_getch()) {
				case 224:
					switch (_getch()) {
					case 72:case 75:
						if (w <= 1) {
							w = 2;
						}
						else w--;
						break;
					case 80:case 77:
						if (w >= 2) {
							w = 1;
						}
						else w++;
						break;
					}
					goto a;
					break;
				case 13:
					if (w == 1) { // pag yes
						
						for (auto& book : tempb) {
							if (book.title == s) {
								found = true;
								
								book.title = ntitle;
								book.author = nauthor;
								book.availability = navailability;
								book.year = nyear;
								book.location = nlocation;
								book.isbn = nisbn;
							}
						}
						if (!found) {
							gotoxy(80, 5); cout << "Book not found!";
							return;
						}
						ofstream Record("Book_Record.txt");
						if (Record.is_open()) {
							for (const auto& book : tempb) {
								Record << book.title << '\t' << book.author << '\t'
									<< book.availability << '\t' << book.year << '\t'
									<< book.location << '\t' << book.isbn << '\n';
							}
							Record.close();
							gotoxy(25, 1); cout << "Book successfully edited!";
							Sleep(1000);
							break;
						}
						else {
							cout << "Unable to open file for writing!";
						}
						break;
					}
					else if (w == 2) { // pag no
						return;
						break;
					}
					break;
				}
				break;
			}
			break;
		case 2:// pag no
			break;
		}

	}
}

void delBook(string& s) { // goods na 
	system("cls");
	table(3, 1, 1);
	vector<Book> tempstor;
	string title, author, availability, year, location, callno;
	int counter = 2;
	bool notfound = false;

	fstream Record("Book_Record.txt", ios::in);
	if (Record.is_open()) {
		string line;
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
				gotoxy(67, 12); cout << availability;
				gotoxy(52, 12); cout << year;
				gotoxy(82, 12); cout << location;
				gotoxy(102, 12); cout << callno;

			}
			tempstor.push_back({ title, author, year, availability, location, callno });
		}
		Record.close();
	}
	else {
		gotoxy(45, 2); cout << "Unable to open file!" << endl;
		return;
	}
	auto it = remove_if(tempstor.begin(), tempstor.end(), [&s](const Book& book) { // pang hanap tas pang remove sa txt file
		return book.title == s;
		});

	gotoxy(38, 2); cout << "Are you sure do you want to delete this book?";

confi:
	hc(1);
	c(7); button(45, 3, 10, "yes", 0);
	c(7); button(60, 3, 10, "no", 0);

	if (counter == 1) {
		c(4); button(45, 3, 10, "", 0);
	}
	else if (counter == 2) {
		c(4); button(60, 3, 10, "", 0);
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
			if (counter >= 2) {
				counter = 1;
			}
			else counter++;
			break;
		}
		goto confi;
		break;
	case 13:
		if (counter == 1) {
			// yes	

			tempstor.erase(it, tempstor.end()); // pang remove sa vector

			Book* head = NULL;
			Book* secBook = NULL;

			for (const auto& book : tempstor) {// condition to iterate
				Book* newBook = new Book(book);
				newBook->next = NULL;

				if (!head) {
					head = newBook; // unang book
					secBook = head;
				}
				else {
					secBook->next = newBook; // dugtungan
					secBook = newBook;
				}
			}
			Book* display = head;
			ofstream Record("Book_Record.txt");
			if (Record.is_open()) {
				while (display) {
					Record << display->title << '\t'
						<< display->author << '\t'
						<< display->availability << '\t'
						<< display->year << '\t'
						<< display->location << '\t'
						<< display->isbn << '\n';
					display = display->next;
				}
				Record.close();
			}
			else {
				gotoxy(45, 2); cout << "Unable to open file for writing!" << endl;
			}

			for (int i = 2; i < 6; i++)
			{
				gotoxy(20, i); cout << string(100, ' ');
			}
			gotoxy(45, 2); cout << "Book has been deleted!";
			Sleep(1000);
			break;

		}
		else if (counter == 2) {// back;
			return;
		}

	}


}

bool A2Z(const Book a, const Book b) { // condition is required to be an object
	if ((a.title == b.title) || (a.title == "" && b.title == "")) {
		return a.author < b.author;
	}
	else {
		return a.title < b.title;
	}
}

bool category(const Book a, const Book b) {
	return a.location < b.location;
}

void sorting(int a) { //SOTING FUNCTIONN (goods)
	system("cls");
	
	int h = 1;
	Book book;
	vector<Book> tempst;
	ifstream Record("Book_Record.txt");
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
				tempst.push_back(book);
			}
		}
		Record.close();
	}
	else {
		cout << "Unable to open the file";
	}

	if (a == 1) {
		sort(tempst.begin(), tempst.end(), A2Z); // dito nya isosort
	}
	else if (a == 2) {
		sort(tempst.begin(), tempst.end(), category);
	}

	for (int i = 0; i <= tempst.size(); i++) {
		h++;
	}
	table(h, 1, 1);

	int z = 0, y = 0;
	for (int i = 2; i < h; i++)
	{
		gotoxy(5, 12 + y); cout << string(20, ' ');
		gotoxy(28, 12 + y); cout << string(20, ' ');
		gotoxy(52, 12 + y); cout << string(8, ' ');
		gotoxy(67, 12 + y); cout << string(4, ' '); // erasing display lang sa table
		gotoxy(82, 12 + y); cout << string(13, ' ');
		gotoxy(102, 12 + y); cout << string(15, ' ');
		y++;
	}
	for (const auto& book : tempst) {

		gotoxy(5, 12 + z); cout << book.title;
		gotoxy(28, 12 + z); cout << book.author;
		gotoxy(52, 12 + z); cout << book.availability;
		gotoxy(67, 12 + z); cout << book.year;
		gotoxy(82, 12 + z);	cout << book.location;
		gotoxy(102, 12 + z); cout << book.isbn;
		z++;
	}
}

void view_all() { // not done yet tho goods nadin
	system("cls");

	int y = 0;
	int counter = 1;
	int h = 2;
	gotoxy(45, 2); cout << "ALL BOOKS!";

	string title, author, year, availability, location, callno;

	ifstream Record("Book_Record.txt");
	if (Record.is_open()) {
		string line;
		while (getline(Record, line)) {
			stringstream ss(line);
			getline(ss, title, '\t');
			getline(ss, author, '\t');
			getline(ss, year, '\t');
			getline(ss, availability, '\t');
			getline(ss, location, '\t');
			getline(ss, callno, '\t');

			gotoxy(5, 12 + y); cout << title;
			gotoxy(28, 12 + y); cout << author;
			gotoxy(67, 12 + y); cout << availability;
			gotoxy(52, 12 + y); cout << year;
			gotoxy(82, 12 + y); cout << location;
			gotoxy(102, 12 + y); cout << callno;
			y++;
			h++;
		}
		Record.close();
	}
	else {
		cout << "Unable to open file!" << endl;
	}
	table(h, 1, 1);
m:
	hc(1);
	c(7); button(4, 5, 14, "A-Z", 0);
	c(7); button(21, 5, 15, " Category", 0);
	c(7); button(39, 5, 14, "Back", 0);

	if (counter == 1) {
		c(4); button(4, 5, 14, "", 0);
	}
	else if (counter == 2) {
		c(4); button(21, 5, 15, "", 0);
	}
	else if (counter == 3) {
		c(4); button(39, 5, 14, "", 0);
	}

	switch (_getch()) {
	case 224:
		switch (_getch()) {
		case 72:case 75:
			if (counter <= 1) {
				counter = 3;
			}
			else counter--;
			break;
		case 80:case 77:
			if (counter >= 3)
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
			sorting(1);
			goto m;
			break;
		case 2:
			sorting(2);
			goto m;
			break;
		case 3:// back
			return;
			break;


		}
	}
}



void modilete() {
a:
	system("cls");
	char d;
	string title = "", author = "", availability = "", year = "", location = "", isbn = "";
	int counter = 0, y = 0, h = 3;
	string searchbook;
	string search, line;
	vector<string> sug;
	ifstream Record("Book_Record.txt");
	if (Record.is_open()) {
		while (getline(Record, line)) {
			stringstream ss(line);
			getline(ss, title, '\t');
			getline(ss, author, '\t');
			getline(ss, availability, '\t');
			getline(ss, year, '\t');
			getline(ss, location, '\t');
			getline(ss, isbn, '\t');
			sug.push_back(title);  // Store titles
			sug.push_back(author);  // Store authors
			sug.push_back(isbn); // Store isbn
		}
		Record.close();
	}

M:  

	gotoxy(70, 2); cout << char(218) << string(37, char(196)) << char(191);
	gotoxy(70, 3); cout << char(179);
	gotoxy(71, 3); cout << "Search:" << char(179);
	gotoxy(108, 3); cout << char(179);
	gotoxy(70, 4); cout << char(192) << string(37, char(196)) << char(217);
	gotoxy(80, 3); cout << string(15, ' '); // Clear previous input


	for (int i = 0; i < y; i++) {
		gotoxy(4, 13 + y); cout << string(21, ' ');
		gotoxy(26, 13 + y); cout << string(24, ' ');
		gotoxy(51, 13 + y); cout << string(14, ' '); //pang erase sa extra lines
		gotoxy(66, 13 + y); cout << string(8, ' ');
		gotoxy(75, 13 + y); cout << string(21, ' ');
		gotoxy(97, 13 + y); cout << string(20, ' ');
	}
	table(h + y, 1, 2);

	(7); button(10, 5, 15, "Edit", 0);
	c(7); button(30, 5, 15, "Delete", 0);
	c(7); button(50, 5, 14, "Back", 0);
	gotoxy(80, 3); cout << string(15, ' ');

	switch (counter) {
	case 0:
		hc(0);
		gotoxy(80, 3);
		for (int j = 0;;) {
			d = _getch();
			if (d == -32) {
				d = _getch();
				if (d == 72 || d == 75) {
					counter = 1;
					break;
				}
				else if (d == 80 || d == 77) {
					counter++;
					break;
				}
			}
			else if (d == 8 && j > 0) { // Backspace
				gotoxy(80 + j, 3); cout << "\b \b";
				searchbook.pop_back();
				--j;
				for (int i = 0; i < 5; i++) {
					gotoxy(80, 5 + i);
					cout << string(20, ' '); // Clear previous suggestions
				}
				gotoxy(80 + j, 3);
			}
			else if ((d >= 'a' && d <= 'z') || (d >= 'A' && d <= 'Z') || (d == ' ' && j < 32)) {
				int x = 0;
				gotoxy(80 + j, 3); cout << d;
				searchbook += d;
				++j;
				auto filtered = getSuggestions(sug, searchbook);

				for (x = 0; x < 5; ++x) {
					gotoxy(80, 5 + x);
					cout << string(20, ' '); // Clear suggestion area
				}
				x = 0; // Reset x for displaying suggestions
				for (const auto& suggestion : filtered) {
					gotoxy(80, 5 + x);
					cout << suggestion; // Display suggestion
					x++;
				}
				gotoxy(80 + j, 3);
			}
			else if (d == 13) { // Enter key
				for (int x = 0; x < 5; ++x) {
					gotoxy(80, 5 + x);
					cout << string(20, ' '); // Clear suggestion area
				}
				search = searchbook;
				ifstream record("Book_Record.txt");
				if (record.is_open()) {
					bool found = false;
					for (int i = 0; i < y; i++) {
						gotoxy(5, 13 + i); cout << string(15, ' ');
						gotoxy(28, 13 + i); cout << string(15, ' ');
						gotoxy(52, 13 + i); cout << string(8, ' ');
						gotoxy(67, 13 + i); cout << string(4, ' '); // erasing display lang sa table
						gotoxy(82, 13 + i); cout << string(13, ' ');
						gotoxy(102, 13 + i); cout << string(15, ' ');
					}
					while (getline(record, line)) {
						stringstream ss(line);
						getline(ss, title, '\t');
						getline(ss, author, '\t');
						getline(ss, availability, '\t');
						getline(ss, year, '\t');
						getline(ss, location, '\t');
						getline(ss, isbn, '\t');
						if (title == search || author == search || isbn == search) {
							found = true;
							gotoxy(5, 13 + y); cout << title;
							gotoxy(28, 13 + y); cout << author;
							gotoxy(52, 13 + y); cout << availability;
							gotoxy(67, 13 + y); cout << year;
							gotoxy(82, 13 + y); cout << location;
							gotoxy(102, 13 + y); cout << isbn;
							y++;
						}

					}
					sug.clear();
					sug.shrink_to_fit();
					searchbook = "";
					record.close();
					if (!found) {
						gotoxy(10, 1); c(4); cout << "No results found."; c(7);
						Sleep(500);
						gotoxy(10, 1); cout << string(25, ' '); // Clear message
					}
				}
				else {
					gotoxy(80, 1); cout << "Unable to open file!";
					Sleep(500);
					gotoxy(80, 1); cout << string(25, ' ');
				}
				break;
			}
		}
		goto M;
		break;
	case 1:
		hc(1);
		c(4); button(10, 5, 15, "", 0); // edit
		switch (_getch()) {
		case 224:
			switch (_getch()) {
			case 72:case 75:
				counter--;
				break;
			case 80:case 77:
				counter++;
				break;
			}
			goto M;
			break;
		case 13:
			if (search != "") {
				edit(search);
				goto a;
			}
			else {
				gotoxy(5, 2); cout << "ERROR! you must search a book first!";
				Sleep(1000);
				gotoxy(5, 2); cout << string(40, ' ');
				counter = 0;
				goto M;
			}
			break;
		}
		goto M;
		break;
	case 2:
		hc(1);
		c(4); button(30, 5, 15, "", 0); // delete
		switch (_getch()) {
		case 224:
			switch (_getch()) {
			case 72:case 75:
				counter--;
				break;
			case 80:case 77:
				counter++;
				break;
			}
			goto M;
			break;
		case 13:
			if (search != "") {
				delBook(search);
				goto a;
			}
			else {
				gotoxy(5, 2); cout << "ERROR! you must search a book first!";
				Sleep(1000);
				gotoxy(5, 2); cout << string(40, ' ');
				counter = 0;
				goto M;
			}
			break;
		}
		goto M;
		break;
	case 3:
		hc(1);
		c(4); button(50, 5, 14, "", 0); // BACK
		switch (_getch()) {
		case 224:
			switch (_getch()) {
			case 72:case 75:
				counter--;
				break;
			case 80:case 77:
				counter = 0;
				break;
			}
			goto M;
			break;
		case 13:
			break;
		}
		break;
	}
}

void bookRecord(int s) {
	const int OPTIONS = 4;
	int size = s;
	char x = 0, y = 1;
e:

	system("cls");
A:
	hc(1);
	for (int i = 1; i <= OPTIONS; ++i) {
		if (i == y) {
			c(3);
			// Highlight the selected option
			for (int j = 0; j < 30; j++) {
				gotoxy(62 + j, 8 + (i - 1) * 4); cout << char(220);
				gotoxy(62 + j, 11 + (i - 1) * 4); cout << char(220);
			}

			for (int j = 0; j < 3; j++) {
				gotoxy(62, 8 + (i - 1) * 4 + j); cout << char(220);
				gotoxy(91, 8 + (i - 1) * 4 + j); cout << char(220);
			}
		}
		else {
			c(7);
			// Draw non-selected options
			for (int j = 0; j < 30; j++) {
				gotoxy(62 + j, 8 + (i - 1) * 4); cout << char(220);
				gotoxy(62 + j, 11 + (i - 1) * 4); cout << char(220);
			}

			for (int j = 0; j < 3; j++) {
				gotoxy(62, 8 + (i - 1) * 4 + j); cout << char(220);
				gotoxy(91, 8 + (i - 1) * 4 + j); cout << char(220);
			}
		}
		// Display menu options text
		if (i == 1) {
			if (i == y)
				c(7); gotoxy(63, 10); cout << " 1. Add Book";
		}
		else if (i == 2) {
			if (i == y)
				c(7); gotoxy(63, 14); cout << " 2. Modify/Delete Book";
		}
		else if (i == 3) {
			if (i == y)
				c(7); gotoxy(63, 18); cout << " 3. View all Book";
		}
		else if (i == 4) {
			if (i == y)
				c(7); gotoxy(63, 22); cout << " 4.  Back";
		}

	}

	c(7);
	gotoxy(20, 22); cout << "Use arrow keys to navigate ";
	gotoxy(20, 23); cout << "and press Enter key to select ";
	gotoxy(17, 2); cout << "Press F2 key to go to Help option:";

	switch (_getch()) {
	case 224:
		switch (_getch()) {
		case 72:case 75:
			if (y <= 1) {
				y = 4;
			}
			else y--;
			break;
		case 80:case 77:
			if (y >= 4) {
				y = 1;
			}
			else y++;
			break;
		}
		goto A;
		break;
	case 13:

		if (y == 1) {//add book
			system("cls");
			int p = 0;
			int h = 4;
			bool added = true;
		t:
			int acount = 2;
			added = add(p, size);
			if (!added) {
				goto e;
			}
			else {
			confi:
				hc(1);
				gotoxy(15, 4); cout << "Do want to add more books?";

				c(7); button(15, 5, 10, "yes", 0);
				c(7); button(30, 5, 10, "no", 0);

				if (acount == 1) {
					c(4); button(15, 5, 10, "", 0);
				}
				else if (acount == 2) {
					c(4); button(30, 5, 10, "", 0);
				}

				switch (_getch()) {
				case 224:
					switch (_getch()) {
					case 72:case 75:
						if (acount == 1) {
							acount = 2;
						}
						else acount--;
						break;
					case 80:case 77:
						if (acount == 2) {
							acount = 1;
						}
						else acount++;
						break;
					}
					goto confi;
					break;
				case 13:
					if (acount == 1) {
						p++;
						goto t;
					}
					else goto e;
					break;
				}
			}
			break;
		}
		else if (y == 2) {// modify/delete book
			modilete();
			goto e;
			break;
		}
		else if (y == 3) {//view all book
			view_all();
			goto e;
			break;
		}
		else if (y == 4) { //back
			break;
		}



	}

}
