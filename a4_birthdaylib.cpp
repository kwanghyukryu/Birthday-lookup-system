// Kwanghyuk Ryu
// 301475831
// kra69

#include "a4_birthdaylib.hpp"
#include <iostream>

using namespace std;

//the structure used for holding one birthday entry


//Creates a Birthday struct variable storing three short representing 
// year, month, and day respectively, a string representing a name,
// and a string representing a trait (knownFor)
//Returns the address of the dynamically (i.e., uses malloc) created variable
//For example:
//Given the code:
//Birthday* person = create_Birthday(1985, 1, 1, 
//                                      "J. Edgar Hoover",
//                                      "First director of the FBI");
//cout << person->year << "-" << person->month << "-" << person->day << endl
//<< person->name << endl << person->knownFor;
//will result in an output like this:
//1985-1-1
//J. Edgar Hoover
//First director of the FBI
Birthday* create_Birthday(short year, short month, short day, string name, string knownFor) {
  Birthday *person;
  person = new Birthday;// Allocate memory for the Birthday struct
  person->year = year;// Store the values in the struct
  person->month = month;
  person->day = day;
  person->name = name;
  person->knownFor = knownFor;
  return person;// Return the address of the struct
}
        

//Releases the memory created to store the 2 members name and knownFor using
// the address of a Birthday struct variable
//Note that the person parameter can be NULL
// and if this is the case the function should do nothing.
//This function now also releases the memory used for the Birthday struct variable,
// and since string is used there really is no need to handle name and knownFor
void delete_Birthday(Birthday* person){
    if(person == nullptr){
        return;
    }
    delete person;
    person = nullptr;
}
//helper function printing a Birthday struct variable nicely
void print_Birthday(Birthday* person, ostream& os){
    os << person->year << "-" << person->month << "-" << person->day << endl << person->name << endl << person->knownFor;
}
//helper function for comparing birthdays by month and day
//-ve means p1 is "smaller" than p2, +ve means the other way
//0 means they are "the same"
int compareBirthdaysByMD(const Birthday* p1, const Birthday* p2) {
    const Birthday* person1 = *(const Birthday**)p1;
    const Birthday* person2 = *(const Birthday**)p2;
    if (person1->month < person2->month) {//if the second month is first then the first, return -1 which changes the placement
      return -1;
    }else if (person1->month > person2->month){//if the first month is first, return 1 which keeps the first one ahead
      return 1;
    }else{//if the months equal
        if (person1->day > person2->day){//if first day is first return 1 which keeps its placement
          return 1;
        }else if (person1->day < person2->day){//if second day is first, return -1 which swaps its place
          return -1;
        }else{//if they match, return original placement
          return 0;
        } 
      }
  }
