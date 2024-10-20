#include <iostream>
#include <fstream>
#include <gotoxy.h>
#include "options.cpp"

using namespace std;


int main() {
    int size = 0;

    fstream Records("Book_Record");
    if (Records.is_open()) {
        string line;
        while (getline(Records, line)) {
            ++size;
        }
    }Records.close();

start:
    system("cls");
    char x = 0, y = 0;
    char i = 0, a = 0;
    char username[32], password[32];
    char user[] = "User1", uspass[] = "User1";
    char admin[] = "Admin", adpass[] = "Admin";
    int access = 0;
    // Border();
     //bchain();
     //Bookone();
    c(3); // color(color id)
    //borderlog();

    c(7); gotoxy(75, 10); cout << "LOG IN";
    gotoxy(65, 13);  cout << "Username: ";
    gotoxy(65, 16); cout << "Password: ";

Login:
    hc(0);// pang hide ng cursor(1 == hide, 0 == visible)
    gotoxy(76, 13);
    for (int i = 0;;) { // Login security for username
        a = _getch();
        if (a >= 'a' && a <= 'z' || a >= 'A' && a <= 'Z' || a >= '0' && a <= '9' || a == ' ') {
            if (i < 19) {
                cout << a;
                username[i] = a;
                ++i;
            }
        }
        else if (a == 8 && i >= 1) {
            cout << "\b \b";
            username[--i] = '\0';
        }
        else if (a == 13 && i != 0) {
            username[i] = '\0';
            break;
        }
        else {
            a = _getch();
        }
    }
    gotoxy(76, 16);
    for (int i = 0;;) { // login security for password
        a = _getch();
        if (a >= 'a' && a <= 'z' || a >= 'A' && a <= 'Z' || a >= '0' && a <= '9' || a == ' ') {
            if (i < 19) {
                cout << "*";
                password[i] = a;
                ++i;
            }
        }
        else if (a == 8 && i >= 1) {
            cout << "\b \b";
            password[--i] = '\0';
        }
        else if (a == 13) {
            password[i] = '\0';
            if ((strcmp(username, user) == 0 && strcmp(password, uspass) == 0) || strcmp(username, admin) == 0 && strcmp(password, adpass) == 0) { // For logging in
                if (strcmp(username, admin) == 0 && strcmp(password, adpass) == 0) {
                    access = 1; // admin access
                }
                break;
            }
            else {
                i = 0;
                gotoxy(50, 19); cout << "Incorrect Username or Password";
                gotoxy(76, 13); cout << string(19, ' ');
                gotoxy(76, 16); cout << string(19, ' ');
                goto Login;
            }
        }
        else {
            switch (_getch()) {
            case 72:
                gotoxy(76, 13); cout << string(19, ' ');
                gotoxy(76, 16); cout << string(19, ' ');
                goto Login;
                break;
            }
        }
    }

main:
    hc(1);
    if (access == 1) {
    Menu:
        system("cls");
        //Bookone();
        //Border();
        //bchain();
        c(7);
        char choice = ' ';
        const int OPTIONS = 5;
        int x = 0, y = 1;

        do {

            gotoxy(72, 7);
            cout << "Main Menu" << endl;
            // Display menu options
            for (int i = 1; i <= OPTIONS; ++i) {
                if (i == y) {
                    c(3);
                    for (int j = 0; j < 30; j++) { // Highlight the selected option
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
                    for (int j = 0; j < 30; j++) { // Draw non-selected options
                        gotoxy(62 + j, 8 + (i - 1) * 4); cout << char(220);
                        gotoxy(62 + j, 11 + (i - 1) * 4); cout << char(220);
                    }

                    for (int j = 0; j < 3; j++) {
                        gotoxy(62, 8 + (i - 1) * 4 + j); cout << char(220);
                        gotoxy(91, 8 + (i - 1) * 4 + j); cout << char(220);
                    }
                }
                if (i == 1) {// Display menu options text
                    if (i == y)
                        c(7); gotoxy(63, 10); cout << " 1.Book Collection Record ";
                }
                else if (i == 2) {
                    if (i == y)
                        c(7); gotoxy(63, 14); cout << " 2.Search Book Information ";
                }
                else if (i == 3) {
                    if (i == y)
                        c(7); gotoxy(63, 18); cout << " 3.Summary Status Report  ";
                }
                else if (i == 4) {
                    if (i == y)
                        c(7); gotoxy(63, 22); cout << " 4. Log out";
                }
                else if (i == 5) {
                    if (i == y)
                        c(7); gotoxy(63, 26); cout << " 5. Exit";
                }
            }
            c(7);
            gotoxy(20, 22); cout << "Use arrow keys to navigate ";
            gotoxy(20, 23); cout << "and press Enter key to select ";
            gotoxy(17, 2); cout << "Press F2 key to go to Help option:";

            int key = _getch();
            if (key == 0 || key == 224) { // Extended key
                key = _getch(); // Read the actual key code
                if (key == 72 || key == 75) { // Up arrow key
                    if (y <= 1) {
                        y = OPTIONS;
                    }
                    else y--;
                }
                else if (key == 80 || key == 77) { // Down arrow key
                    if (y >= OPTIONS) {
                        y = 1;
                    }
                    else y++;
                }
                else if (key == 60) { // F2 key
                    system("cls");
                    // Help();
                    goto Menu;
                    break;
                }
            }
            else if (key == 13) { // Enter key
                if (y == 1) {
                    system("cls");
                    choice = '1';
                    bookRecord(size);
                    goto main;
                    break;
                }
                else if (y == 2) {
                    choice = '2';
                    system("cls");
                    search();
                    //search
                    goto main;
                    break;
                }
                else if (y == 3) {
                    choice = '3';
                    //renting (wala pa dito )
                }
                else if (y == 4) {
                    choice = '4';
                    goto start;
                    break;
                }
                else if (y == 5) {
                    system("cls");
                    choice = '5';
                    //Exit();
                    goto Menu;
                    break;
                }
            }

        } while (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5');
        goto main;


    }
    else {
    normaluser:
        system("cls");
        //Bookone();
        //Border();
        //bchain();
        c(7);
        char choice = ' ';
        const int OPTIONS = 4;
        int x = 0, y = 1;

        do {

            gotoxy(72, 7); cout << "Main Menu";
            for (int i = 1; i <= OPTIONS; ++i) {   // Display menu options
                if (i == y) {
                    c(3);
                    for (int j = 0; j < 30; j++) {  // Highlight the selected option
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
                    for (int j = 0; j < 30; j++) {// Draw non-selected options
                        gotoxy(62 + j, 8 + (i - 1) * 4); cout << char(220);
                        gotoxy(62 + j, 11 + (i - 1) * 4); cout << char(220);
                    }
                    for (int j = 0; j < 3; j++) {
                        gotoxy(62, 8 + (i - 1) * 4 + j); cout << char(220);
                        gotoxy(91, 8 + (i - 1) * 4 + j); cout << char(220);
                    }
                }

                if (i == 1) {// Display menu options text
                    if (i == y)
                        c(7); gotoxy(63, 10); cout << " 1.Search Book Information ";
                }
                else if (i == 2) {
                    if (i == y)
                        c(7); gotoxy(63, 14); cout << " 2.Summary Status Report ";
                }
                else if (i == 3) {
                    if (i == y)
                        c(7); gotoxy(63, 18); cout << " 3. Log out ";
                }
                else if (i == 4) {
                    if (i == y)
                        c(7); gotoxy(63, 22); cout << " 4. Exit";
                }

            }
            c(7);
            gotoxy(20, 22); cout << "Use arrow keys to navigate ";
            gotoxy(20, 23); cout << "and press Enter key  to select ";
            gotoxy(17, 2); cout << "Press F2 key to go to Help option:";

            // Detect keypress
            int key = _getch();
            if (key == 0 || key == 224) { // Extended key
                key = _getch(); // Read the actual key code
                if (key == 72 || key == 75) { // Up arrow key
                    if (y <= 1) {
                        y = OPTIONS;
                    }
                    else y--;
                }
                else if (key == 80 || key == 77) { // Down arrow key
                    if (y >= OPTIONS) {
                        y = 1;
                    }
                    else y++;
                }
                else if (key == 60) { // F2 key
                    system("cls");
                    //Help();
                    goto normaluser;      // Call displayHelp function
                }
            }
            else if (key == 13) { // Enter key
                if (y == 1) {
                    system("cls");
                    choice = '1';
                    //search
                    search();
                    goto main;


                }
                else if (y == 2) {
                    system("cls");
                    choice = '2';
                    //renting
                }
                else if (y == 3) {
                    choice = '3';
                    goto start;
                }
                else if (y == 4) {
                    system("cls");
                    choice = '4';
                    //Exit();
                    goto normaluser;
                }

            }

        } while (choice != '1' && choice != '2' && choice != '3' && choice != '4');
        goto main;
    }


    system("pause");
}
