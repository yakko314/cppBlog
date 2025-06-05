//
// Created by lam on 03.06.2025.
//

#include "Date.h"

Date::Date(const unsigned int &day, const unsigned int &month, const unsigned int &year) {
    if (month < 1 || month > 12) {
        throw std::invalid_argument("Invalid month: " + std::to_string(month));
    }
    if (day < 1 || day > 31) {
        throw std::invalid_argument("Invalid day: " + std::to_string(day));
    }
    if (month == 2 && day == 29 && year % 4 != 0) {
        throw std::invalid_argument("Invalid date: " + std::to_string(year) + " is not a leap year");
    }
    this->day = day;
    this->month = month;
    this->year = year;

}

std::ostream & operator<<(std::ostream &os, const Date &date) {
    os << date.day << "." << date.month << "." << date.year;
    return os;
}
