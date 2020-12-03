// implementation for the header file of the aclass class
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
#include "aclass.h"
using namespace std;


// default constructor initialize everthing to empty string
aclass::aclass(){
	dept = "";
	coursenum = "";
	title = "";
	day = "";
	starttime = "";
	endtime = "";
	room = "";
}

// constructor
aclass::aclass(string dept_, string coursenum_, string title_, string day_, string starttime_, string endtime_, string room_){
	dept = dept_;
	coursenum = coursenum_;
	title = title_;
	day = day_;
	starttime = starttime_;
	endtime = endtime_;
	room = room_;
}

// get the department name
string aclass::getdept() const{
	return dept;
}

// get course number
string aclass::getcoursenum() const{
	return coursenum;
}

// get class title
string aclass::gettitle() const{
	return title;
}

// get day of the class
string aclass::getday() const{
	return day;
}

// get start time
string aclass::getstarttime() const{
	return starttime;
}

// get end time
string aclass::getendtime() const{
	return endtime;
}

// get the room for the class
string aclass::getroom() const{
	return room;
}