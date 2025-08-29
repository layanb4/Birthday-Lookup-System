#include <stdio.h>
#include "a4_birthdaylib.hpp"
#include <iostream>


//setting the information in the struct
Birthday* create_Birthday(short year, short month, short day,
                            string name, string knownFor){

    //allocating memory for the struct
    Birthday* bbday = new Birthday();

    //putting the info for year, month, and day
    if(bbday != NULL){
    bbday->year = year;
    bbday->month = month;
    bbday->day = day;
    bbday->name = name;
    bbday->knownFor = knownFor;
    }

    //returning the struct
    return bbday;
}

void delete_Birthday(Birthday* person){

    //if it is empty, do the following
     if(person == nullptr){
        return;
    }
    //otherwise delete
    else{
        delete person;
    }
}


//print the information in the following format
void print_Birthday(Birthday* person, ostream& os){
   cout << person->year << "-" << person->month << "-";
    cout<< person->day << endl;
   cout << person->name << endl;
   cout << person->knownFor;
}

//helper function for to compare birthdays by month and day
int compareBirthdaysByMD(const Birthday* p1, const Birthday* p2){

    //if the first birthday is less than the second birthday 
    //then return a -1 so quicksort knows to switch the order
    if(p1->month < p2->month){
        return p1->month - p2->month;
    }

    //if the months are the same, compare the days
    //and if the first day is less than the second return a -1 to switch
    else if(p1->month == p2->month){
        if(p1->day < p2->day){
            return p1->day-p2->day;

        }
        //otherwise just print
        else{
            return p2->day;
        }
    }  
return 0;}


