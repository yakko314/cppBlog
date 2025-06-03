//
// Created by lam on 03.06.2025.
//

#include "Comment.h"


#define RESET   "\033[0m"
#define BLUE    "\033[34m"
#define GREEN   "\033[32m"

Comment::Comment(const string &username, const string &content, const Date &date)
    : username(username), content(content), date(date) {


}

std::ostream & operator<<(std::ostream &os, const Comment &comment) {
    os << GREEN << comment.username << RESET << ": " << comment.content << " | " << BLUE << comment.date << RESET;
    return os;
}
