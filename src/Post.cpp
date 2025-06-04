//
// Created by lam on 18.05.2025.
//

#include "Post.h"

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */


Post::Post(const int& id, const string& title, const string& file, const string& content, const Date& date)
    : id(id), title(title), file(file), content(content), date(date) {
}

void Post::Like() {
    stats.Like();
}

void Post::Dislike() {
    stats.Dislike();
}

void Post::Love() {
    stats.Love();
}


void Post::addComment(const Comment &comment) {
    comments.push_back(comment);
}


void Post::bigPrint(std::ostream& os) const {
    os <<
        //id << " | " //folosit pentru testare, programul foloseste index-ul vectorului in loc de id
    BOLDMAGENTA<< title << RESET << " | "
    BOLDRED<< file << RESET << " | "
    BLUE<< date << RESET << " | "
    << stats << " | "
    << '\n' << content
    << YELLOW;
    if (comments.empty()) {
        os << "\t(No comments yet)\n" << RESET;
    } else {
        os << "\n" << comments.size() << " comentarii:\n" << RESET;
        for (const auto& comment : comments) {
            os << "\t-" << comment << '\n';
        }
    }
}

ostream & operator<<(ostream &os, const Post &post) {
    os <<
    //post.id << " | " << //folosit pentru testare, programul foloseste index-ul vectorului in loc de id
    BOLDMAGENTA << post.title << RESET << " | "
    << "Fișier: " BOLDRED << post.file << RESET << " | "
    BLUE << post.date << RESET " | "
    << post.stats << " | "
    YELLOW << post.comments.size() << " Comentarii" << RESET;
    return os;
}
