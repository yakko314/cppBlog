//
// Created by lam on 03.06.2025.
//

#include "Date.h"

Date::Date(const unsigned int &day, const unsigned int &month, const unsigned int &year) {
    if (month < 1 || month > 12) {
        throw "Invalid month";
    }
    if (day < 1 || day > 31) {
        throw "Invalid day";
    }
    if (month == 2) {
        if (day == 29) {
            if (year % 4 != 0) {
                throw "Invalid day, not leap year";
            }
        }
    }
    this->day = day;
    this->month = month;
    this->year = year;

}

std::ostream & operator<<(std::ostream &os, const Date &date) {
    os << date.day << "/" << date.month << "/" << date.year;
    return os;
}
