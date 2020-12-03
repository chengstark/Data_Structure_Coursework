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
#include <set>
#include <iterator>
#include "aclass.h"
using namespace std;

// function to read in the file
vector<aclass> fileparser(string filename){
	ifstream infile(filename);
	string line;
	vector<aclass> classes;
    // read in the file line by line
	while (getline(infile, line))
	{	
	    vector<string> aline;
	    stringstream ss(line);
	    string apart;
	    while(getline(ss, apart, ' ')){
	    	aline.push_back(apart);
	    }
        // identify which day it is
	    for(char day: aline[4]){
	    	string weekday_label;
	    	if(day == 'M') weekday_label = "Monday";
	    	if(day == 'T') weekday_label = "Tuesday";
	    	if(day == 'W') weekday_label = "Wednesday";
	    	if(day == 'R') weekday_label = "Thursday";
	    	if(day == 'F') weekday_label = "Friday";
            // create the aclass object with information given
	    	aclass tmpclass(aline[1], aline[2], aline[3], weekday_label, aline[5], aline[6], aline[7]);
            // store the class
	    	classes.push_back(tmpclass);
	    }
	}
	return classes;
}

// the day comparator for sorting the classes by day, from early to late in a week
int daycompare(string a, string b){
	vector<string> dates = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
	if((find(dates.begin(), dates.end(), a)!=dates.end())&&(find(dates.begin(), dates.end(), b)!=dates.end())){
		int distancea = distance(dates.begin(), find(dates.begin(), dates.end(), a));
		int distanceb = distance(dates.begin(), find(dates.begin(), dates.end(), b));
		if(distancea<distanceb) return -1;
		if(distancea>distanceb) return 1;
		if(distancea==distanceb) return 0;
	}
	else{
		return NULL;
	}
	return NULL;
}

// class comparator by room
bool classcompareroom(aclass a, aclass b){
	string aday = a.getday();
	string bday = b.getday();
	string astart = a.getstarttime();
	string bstart = b.getstarttime();
	string aend = a.getendtime();
	string bend = b.getendtime();
	if(daycompare(aday, bday) == -1){ // smaller day
		return true;
	}
	else if(daycompare(aday, bday) == 0){ // same day
		if(astart[5]<bstart[5]){ // smaller AM/PM
			return true;
		}
		else if(astart[5] == bstart[5]){ // same AM/PM
            // dealing with special case of 12:XXPM, make all of them into 00:XXPM
			if(astart[0] == '1'&&astart[1] == '2'){
				astart[0] = '0';
				astart[1] = '0';
			}
			if(bstart[0] == '1'&&bstart[1] == '2'){
				bstart[0] = '0';
				bstart[1] = '0';
			}
			if(astart<bstart){ // smaller time
				return true;
			}
			else{ // bigger time
				return false;
			}
		}
		else{ // bigger AM/PM
			return false;
		}
	}
	else{ // bigger day
		return false;
	}
}

// class comparator by department, adding the comparision between course number as requested
bool classcomparedept(aclass a, aclass b){
	if (a.getcoursenum() < b.getcoursenum()){ // smaller coursenum
		return true;
	}
	else if(a.getcoursenum() == b.getcoursenum()){ // same coursenum
		return classcompareroom(a, b);
	}
	return false;
}


// helper function just to print slashes with a for loop
string printslash(int n){
	string slashes;
	for(int i = 0;i<n;i++){
		slashes+="-";
	}
	return slashes;
}

// custom function to suggest parking location of the day
void getcustom(vector<aclass> classes, ofstream &out){
	int maxregistedroom = 0;
	string maxroomname = "";
	vector<vector<string> > suggestion;
	set<string> rooms;
    // get all names of the room
	for(aclass current_class: classes){
		rooms.insert(current_class.getroom());
	}
    // check if there is any courses
	if(rooms.size() > 0){
		for(string room: rooms){
			int entrycount = 0;
			for(aclass current_class: classes){
				if(current_class.getroom() == room){
					entrycount ++;
				}
			}
            // get the room with the most courses
			if(entrycount>maxregistedroom){
				maxregistedroom = entrycount;
				maxroomname = room;
			}
            // store the rooms for future sorting
			vector<string> aroom;
			aroom.push_back(to_string(entrycount));
			aroom.push_back(room);
			suggestion.push_back(aroom);
		}
        // sort the vector of rooms by number of class holding in that room from small to big
		sort(suggestion.begin(), suggestion.end());
		reverse(suggestion.begin(), suggestion.end());
        // output the result into the file
		out<<"The room with most classes is: "<<maxroomname<<"."<<endl;
		out<<"It has "<<maxregistedroom<<" classes."<<endl;
		out<<"You should avoid parking near this room."<<endl;
		out<<"Here are two suggested parking location (near room) : "<<endl;
        // if there is two or more rooms output two room as suggestions
		if(suggestion.size()>=2){
			out<<suggestion[0][1]<<endl;
			out<<suggestion[1][1]<<endl;
		}
        // if there is only one other room, output the only room as suggestion
		else if(suggestion.size()>0){
			out<<suggestion[0][1]<<endl;
		}
        // if there is only one room in total
		else{
			out<<"Anywhere but "<<maxroomname<<" ."<<endl;
		}
	}
    // nothing in the file, no room no courses at all
	else{
		out<<"No data available."<<endl;
	}

}

void printroom(string room, ofstream &out, vector<aclass> classes, int maxtitlelength, int maxdaylength, int &entrycount){
	out<<"Room "<<room<<endl;
	out<<"Dept  "<<"Coursenum  "<<setw(maxtitlelength)<<left<<"Class Title"<<"  "<<setw(maxdaylength)<<left<<"Day"<<"  Start Time  End Time"<<endl;
	out<<printslash(4)<<"  "<<printslash(9)<<"  "<<printslash(maxtitlelength)<<"  "<<printslash(maxdaylength)<<"  "<<printslash(10)<<"  "<<printslash(8)<<endl;
    // for loop to get all classes
	for(aclass current_class: classes){
		if(current_class.getroom() == room){
			entrycount ++;
			out<<current_class.getdept()<<"  "<<current_class.getcoursenum()<<"    "<<current_class.gettitle();
			for(int i=0;i<(maxtitlelength-current_class.gettitle().size());i++){
				out<<" ";
			}
			out<<"  "<<current_class.getday();
			for(int i=0;i<(maxdaylength-current_class.getday().size());i++){
				out<<" ";
			}
			out<<"  "<<current_class.getstarttime()<<"     "<<current_class.getendtime()<<" "<<endl;
		}
	}
	out<<entrycount<<" entries"<<endl;
	out<<endl;
}


void getroom(int argc, vector<aclass> original_classes, ofstream &out, char *argv[]){
	bool specificroom = false;
	vector<aclass> classes = original_classes;
	sort(classes.begin(), classes.end(), classcompareroom);
	string theroom;
    // check if there is any specified room
	if(argc == 5){
		theroom = argv[4];
		specificroom = true;
	}
    // get all the rooms
	set<string> rooms;
	for(aclass current_class: classes){
		rooms.insert(current_class.getroom());
	}
    // check if there is any room in the file
	if(rooms.count(theroom) > 0||argc == 4){
		for(string room: rooms){
			int maxtitlelength = 11;
			int maxdaylength = 0;
            // calculate the maxinum length for each column of course title and day
			for(aclass current_class: classes){
				if(specificroom){
					if(current_class.getroom()!=theroom){
						continue;
					}
				}
				if(current_class.getroom() == room){
					if(current_class.gettitle().size()>maxtitlelength){
						maxtitlelength = current_class.gettitle().size();
					}
					if(current_class.getday().size()>maxdaylength){
						maxdaylength = current_class.getday().size();
					}
				}
			}
			int entrycount = 0;
			if(specificroom){
                // skip the room thats not the speicifed room if requested
				if(room!= theroom){
					continue;
				}
			}
			// print the output
			printroom(room, out, classes, maxtitlelength, maxdaylength, entrycount);
			
		}
	}
    // if there is no data
	else{
		out<<"No data available."<<endl;
	}
}

void printdept(string thedept, ofstream &out, vector<aclass> classes, int maxtitlelength, int maxdaylength, int &entrycount){
	out<<"Dept "<<thedept<<endl;
	out<<"Coursenum  "<<setw(maxtitlelength)<<left<<"Class Title"<<"  "<<setw(maxdaylength)<<left<<"Day"<<"  Start Time  End Time"<<endl;
	out<<printslash(9)<<"  "<<printslash(maxtitlelength)<<"  "<<printslash(maxdaylength)<<"  "<<printslash(10)<<"  "<<printslash(8)<<endl;
    // for loop to get all the classes
	for(aclass current_class: classes){
		if(current_class.getdept() == thedept){
			out<<current_class.getcoursenum()<<"    "<<current_class.gettitle();
			for(int i=0;i<(maxtitlelength-current_class.gettitle().size());i++){
				out<<" ";
			}
			out<<"  "<<current_class.getday();
			for(int i=0;i<(maxdaylength-current_class.getday().size());i++){
				out<<" ";
			}
			out<<"  "<<current_class.getstarttime()<<"     "<<current_class.getendtime()<<" "<<endl;
			entrycount++;
		}
	}
	out<<entrycount <<" entries"<<endl;
	out<<endl;
}

void getdept(int argc, vector<aclass> original_classes, ofstream &out, char *argv[]){
	vector<aclass> classes = original_classes;
	sort(classes.begin(), classes.end(), classcomparedept);
	string thedept = argv[4];
	int maxtitlelength = 11;
	int maxdaylength = 0;
	int entrycount = 0;
	set<string> depts;
    // calculate the maxinum length for each column of course title and day
	for(aclass current_class: classes){
		depts.insert(current_class.getdept());
	}
	for(aclass current_class: classes){
		if(current_class.getdept()!= thedept){
			continue;
		} 
		if(current_class.gettitle().size()>maxtitlelength){
			maxtitlelength = current_class.gettitle().size();
		}
		if(current_class.getday().size()>maxdaylength){
			maxdaylength = current_class.getday().size();
		}
	}
    // if there is any required departments in the file
	if(depts.count(thedept) > 0){
		for(string dept: depts){
            // skip the ones that is not the specified deparment
			if(dept!= thedept){
				continue;
			}
			// print the output
			printdept(thedept, out, classes, maxtitlelength, maxdaylength, entrycount);
		}
	}
    // if there isnt a specified department in the file
	else{
		out<<"No data available."<<endl;
	}
}

int main(int argc, char* argv[]) {
    // parsing the input arguements
	ofstream out(argv[2]);
	vector<aclass> original_classes = fileparser((string)argv[1]);
    // if room is requested
	if(original_classes.size()==0){
		out<<"No data available."<<endl;
		return 0;
	}
	// if room is requested
	if((string)argv[3] == "room"){
		getroom(argc, original_classes, out, argv);
	}
    // if department is requested
	if((string)argv[3] == "dept"){
		getdept(argc, original_classes, out, argv);
	}
    // call custom function if requested
	if((string)argv[3] == "custom"){
		getcustom(original_classes, out);
	}
	return 0;
}
