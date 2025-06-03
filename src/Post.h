//
// Created by lam on 18.05.2025.
//

#ifndef POST_H
#define POST_H
#include "Stats.h"
#include "Date.h"
#include "Comment.h"
#include <string>
#include <vector>
using namespace std;

class Post {
    int id;
    string title;
    string file;
    string content;
    vector<Comment> comments;
    Stats stats;
    Date date;
public:
    Post(const int& id, const string& title, const string& file, const string& content, const Date& date);
    void Like();
    void Dislike();
    void Love();
    void setStats(const Stats& stats){this->stats = stats;}

    friend ostream& operator<<(ostream& os, const Post& post);
    void bigPrint(std::ostream& os) const;

    void addComment(const Comment& comment);

    vector<Comment> getComments() const { return comments;};
    int getId()const{ return id;}
    Stats getStats() const { return stats;}
};



#endif //POST_H
