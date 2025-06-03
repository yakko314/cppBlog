//
// Created by lam on 03.06.2025.
//

#ifndef COMMENT_H
#define COMMENT_H

#include "Date.h"
#include <string>
using namespace std;

class Comment {
    string username;
    string content;
    Date date;

public:
    Comment(const string& username, const string& content, const Date& date);
    friend std::ostream &operator<<(std::ostream &os, const Comment &comment);
    string getUsername()const{return username;}
    string getContent()const{return content;}
    Date getDate()const{return date;}
};



#endif //COMMENT_H
