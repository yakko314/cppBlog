//
// Created by lam on 03.06.2025.
//

#ifndef COMMENT_H
#define COMMENT_H

#include "Date.h"
#include <string>
using namespace std;

/**
 * @class Comment
 * @brief Un comentariu, continue numele de utilizator al autorului acestuia, continutul si data in care a fost postat.
 */
class Comment {
    string username; ///< Numele autorului comentariului
    string content; ///< Continutul comentariului in sine
    Date date; ///< Data postarii comentariului

public:
    /**
     * @brief Constructor pentru comentariu.
     * @param username nume utilizator
     * @param content continutul comentariului
     * @param date data in care acesta a fost postat
     */
    Comment(const string& username, const string& content, const Date& date);

    /**
     * @brief Supraincarca operatorul de afisare
     * @param os streamul care va fi creat
     * @param comment comentariul care vrem sa afisam, alaturi de detaliile acestuia
     * @return o referinta la stream
     */
    friend std::ostream &operator<<(std::ostream &os, const Comment &comment);
    string getUsername()const{return username;}
    string getContent()const{return content;}
    Date getDate()const{return date;}
};



#endif //COMMENT_H
