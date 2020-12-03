// the header file for aclass class
// aclass represent a class with information like department, class title, course number, day, start time and end time
#ifndef __aclass_h_
#define __aclass_h_
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <iomanip>
#include <sstream>
using namespace std;

class aclass{
public:
	// constructors
	aclass();
	aclass(string dept_, string coursenum_, string title_, string day_, string starttime_, string endtime_, string room_);
	// getters 
	string getdept() const;
	string getcoursenum() const;
	string gettitle() const;
	string getday() const;
	string getstarttime() const;
	string getendtime() const;
	string getroom() const;
private:
	// private members
	string dept;
	string coursenum;
	string title;
	string day;
	string starttime;
	string endtime;
	string room;
};

#endif