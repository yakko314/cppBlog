//
// Created by lam on 03.06.2025.
//

#ifndef DATE_H
#define DATE_H

#include <iostream>

class Date {
    unsigned int day;
    unsigned int month;
    unsigned int year;

public:
    Date(const unsigned int& day, const unsigned int& month, const unsigned int& year);
    friend std::ostream& operator<<(std::ostream& os, const Date& date);
};



#endif //DATE_H
