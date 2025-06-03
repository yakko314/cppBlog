//
// Created by lam on 03.06.2025.
//

#include "Comment.h"

Comment::Comment(const string &username, const string &content, const Date &date)
    : username(username), content(content), date(date) {

}

std::ostream & operator<<(std::ostream &os, const Comment &comment) {
    os << comment.username << ": " << comment.content << " | " << comment.date;
    return os;
}
