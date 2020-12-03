#include <iostream>
#include "time.h"


Time::Time() {
    hour = 0;
    minute = 0;
    second = 0;
};
Time::Time(int iHour, int iMinute, int iSecond) {
    hour = iHour;
    minute = iMinute;
    second = iSecond;
};

// Accessors
int Time::getHour() const{
    return hour;
};
int Time::getMinute() const{
    return minute;
};
int Time::getSecond() const{
    return second;
};

// Modifiers
void Time::setHour(int iHour){
    hour = iHour;
};
void Time::setMinute(int iMinute){
    minute = iMinute;
};
void Time::setSecond(int iSecond){
    second = iSecond;
};

// Other member functions
void Time::PrintAMPM(){
    if (hour < 12){
        // print am time
        std::cout << hour << ":";
        if (minute < 10){
            std::cout << "0" << minute << ":";
        }else {
            std::cout << minute << ":";
        }
        if (second < 10){
            std::cout << "0" << second << " ";
        }else {
            std::cout << second << " ";
        }
        std::cout << "am" << std::endl;
    } else if (hour == 24) {
        std::cout << hour - 24 << ":";
        if (minute < 10){
            std::cout << "0" << minute << ":";
        }else {
            std::cout << minute << ":";
        }
        if (second < 10){
            std::cout << "0" << second << " ";
        }else {
            std::cout << second << " ";
        }
        std::cout << "am" << std::endl;
    } else {
        // print pm time
        if (hour == 12) std::cout << hour << ":";
        else std::cout << hour - 12 << ":";

        if (minute < 10){
            std::cout << "0" << minute << ":";
        }else {
            std::cout << minute << ":";
        }
        if (second < 10){
            std::cout << "0" << second << " ";
        }else {
            std::cout << second << " ";
        }
        std::cout << "pm" << std::endl;
    }
}

// not member functions
bool IsEarlierThan(const Time& t1, const Time& t2){
    bool flag = false;
    if (t1.getHour() < t2.getHour()) flag = true;
    else if (t1.getHour() == t2.getHour()){
        if (t1.getMinute() < t2.getSecond()) flag = true;
        else if (t1.getMinute() == t2.getSecond()) {
            if (t1.getSecond() < t2.getSecond()) flag = true;
        }
    }
    return flag;
};