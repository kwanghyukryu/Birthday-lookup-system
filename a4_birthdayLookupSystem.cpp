// Kwanghyuk Ryu
// 301475831
// kra69
#include <iostream> //standard input/output library
#include <fstream> //library that allows file manipulation
#include <string> //string mmanipulation
#include "a4_birthdayBST.hpp" //header file for the binary search tree
#include "a4_birthdaylib.hpp" //birthday struct header file
using namespace std; //so we dont have to right std:: everytime infront of a function

int main() {
    int used = 0; // to count the entries in the file

    int options = 0; // this variable is to hold the users option choice

    short scanMonth; // used to hold the users choice of month for option 3

    short scanDay; // used to hold the users choice of day for option 3

    short inyear; // used to hold the users input for option 4

    short inmonth;// used to hold the users input for option 4

    short inday; // used to hold the users input for option 4

    short year; // to hold the year value from file

    short month; // to hold month value from file

    short day; // to hold day value from file

    for(int i = 0; i < 50; i++){ //line 8-47 for the banner
    cout << "=";
    }
    cout << endl;
    for(int i = 0; i < 9; i++){
    cout << "=";
    }
    cout << " Famous Birthdays Lookup System ";
    for(int i = 0; i < 9; i++){
    cout << "=";
    }
    cout << endl;
    for(int i = 0; i < 20; i++){
    cout << "=";
    }
    cout << " Kwanghyuk";
    for(int i = 0; i < 20; i++){
    cout << "=";
    }
    cout << endl;
    for(int i = 0; i < 20; i++){
    cout << "=";
    }
    cout << " 301475831";
    for(int i = 0; i < 20; i++){
    cout << "=";
    }
    cout << endl;
    for(int i = 0; i < 19; i++){
    cout << "=";
    }
    cout << "kra69@sfu.ca";
    for(int i = 0; i < 19; i++){
    cout << "=";
    }
    cout << endl;
    for(int i = 0; i < 50; i++){
    cout << "=";
    }
    cout << endl;
        BirthdayBST birthdayTree; // birthday search tree

        Birthday* bday = new Birthday; // dynamic array of birthday struct to hold data

        string bar; //seperator

        string inname; // user input

        string inknownFor; // user input

        string fileholder; // user input

        string filesaver; // user input
        
        string temp; //converts to correct type

        string name ; //name from file

        string knownFor; //knownfor from file
        
    do { // using a do while to ask user what option the want
        cout << "Press numbers 1-6 for the following options and then enter:" << endl;

        cout << "1) to load a birthday file." << endl;

        cout << "2) to list birthdays sorted by Month-Day." << endl;

        cout << "3) to look up a birthday." << endl;

        cout << "4) to add a birthday." << endl;

        cout << "5) to save a birthday." << endl;

        cout << "6) to terminate the program." << endl;

        cout << "options: ";

        cin >> options; // user option

        if (options == 1) { 
            used -= used;
            birthdayTree.~BirthdayBST(); // clears the last binary search tree
            cout << "Enter the name of the file: "; // user input
            cin >> fileholder; // file name goes into fileholder to be used below
            ifstream fin; 
            fin.open(fileholder, ios_base::in); // opens file and set to read
            if (!fin.is_open()) { // checks if the file opened or not
                cout << "cannot be opened" << endl; // 
                cout << "==================================================" << endl;
            } else { // if it opens then it will read the data
                while (!fin.eof()) { // open until eof

                    getline(fin >> ws, temp, '-'); // year until dash
                    year = stoi(temp); // convert the string into an int
                    year = static_cast<short>(year); // convert the int into a short

                    getline(fin >> ws, temp, '-'); 
                    month = stoi(temp);
                    month = static_cast<short>(month);

                    getline(fin >> ws, temp);
                    day = stoi(temp);
                    day = static_cast<short>(day);

                    getline(fin >> ws, name); // gets the name
                    getline(fin >> ws, knownFor); 
                    getline(fin >> ws, bar); // gets the seperator

                    bday = create_Birthday(year, month, day, name, knownFor); // creates a birthday 
                    used++; 
                    birthdayTree.insertNode(bday); // insert the birthday to bst
                }

                delete_Birthday(bday);
                cout << used<< " entries read." << endl; // number of entries
                cout << "==================================================" << endl;
                fin.close(); // close the file
            }
        } if (options == 2) { // prints in order
            birthdayTree.inOrderPrint(cout); 

        } if (options == 3) { //ask for birthday wanted
            cout << "What is the month (choose between 1-12 and press enter)?" << endl;
            cin >> scanMonth;
            cout << "What is the day (choose between 1-31 and press enter)?" << endl;
            cin >> scanDay;
            cout << "Your input is:" << scanMonth << "-" << scanDay << endl;
            if (birthdayTree.findNodeByMD(scanMonth, scanDay) == nullptr) { 
            } else {
            birthdayTree.printAllNodeWithMatchingMD(scanMonth, scanDay, cout); 
            }

        } if (options == 4) { // put in user birthday
            cout << "What is the year (input a 4-digit year)? "; 
            cin >> inyear;
            cout << "What is the month (input 1-12 and press enter)? ";
            cin >> inmonth;
            cout << "What is the day (input 1-31 and press enter)? ";
            cin >> inday;
            cout << "What is the name of the person? ";
            getline(cin >> ws, inname);
            cout << "What is this person known for? ";
            getline(cin, inknownFor);
            cout << "Your input is:" << endl;
            cout << inyear << "-" << inmonth << "-" << inday << endl; 
            cout << inname << endl;
            cout << inknownFor << endl;
            bday = create_Birthday(inyear, inmonth, inday, inname, inknownFor); 
            birthdayTree.insertNode(bday); 
            cout << "Birthday added." << endl;

        } if (options == 5) { // saves current entries to other txt file
            cout << "Enter the name of the file you want to save (include .txt): "; // asks the user for the name of the file they want to save
            cin >> filesaver;
            ofstream fout; 
            fout.open(filesaver, ios_base::out); 
            if (!fout.is_open()) {
                cout << "No birthday file loaded. Load one first." << endl;
            } else {
                birthdayTree.inOrderPrint(fout);  
                int size = birthdayTree.getSize(); 
                cout << size << " entries read." << endl; // # of entries
                fout.close(); 
            }
        } else {
            cout << "Please enter a number from 1-6" << endl; // if user did not enter proper number
        }
        
    } while (options != 6);  
    birthdayTree.~BirthdayBST(); // gets rid of tree
    delete_Birthday(bday); // clears the bday array
    delete bday; 
    cout << "Thank you" << endl;
    return 0;
}