//
// Created by lam on 03.06.2025.
//

#ifndef DATE_H
#define DATE_H

#include <iostream>

/**
 * @class Date
 * @brief Reprezinta o data din calendar.
 */
class Date {
    unsigned int day; ///< ziua din data
    unsigned int month; ///< luna din data
    unsigned int year; ///< anul din data

public:
    /**
     * @brief Constructor pentru Data. Aceasta verifica daca este o data valida.
     * @param day Ziua respectiva
     * @param month Luna respectiva
     * @param year Anul respectiv
     */
    Date(const unsigned int& day, const unsigned int& month, const unsigned int& year);    /**
     * @brief Supraincarca operatorul de afisare
     * @param os streamul care va fi creat
     * @param date data care vrem sa afisam, alaturi de detaliile acesteia
     * @return o referinta la stream
     */
    friend std::ostream& operator<<(std::ostream& os, const Date& date);

    unsigned int getDay() const{return day;}
    unsigned int getMonth() const{return month;}
    unsigned int getYear() const{return year;}
};



#endif //DATE_H
