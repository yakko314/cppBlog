//
// Created by lam on 18.05.2025.
//

#include "Post.h"

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
    os << id << " | " << title << " | " << file << " | " << stats << " | " << date
    << '\n' << content;
    os << "\nComentarii:\n";
    if (comments.empty()) {
        os << "\t(No comments yet)\n";
    } else {
        for (const auto& comment : comments) {
            os << "\t-" << comment << '\n';
        }
    }
}

ostream & operator<<(ostream &os, const Post &post) {
    os <<
    post.id << " | " <<
        post.title << " | " << post.file << " | " << post.date << " | " << post.stats;
    return os;
}
