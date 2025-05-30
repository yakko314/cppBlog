//
// Created by lam on 18.05.2025.
//

#ifndef POST_H
#define POST_H
#include "Stats.h"
#include <string>
#include <vector>
using namespace std;

class Post {
    int id;
    string title;
    string file;
    string content;
    vector<string> comments;
    Stats stats;
public:
    Post(const string& title, const string& file, const string& content);
    void Like();
    void Dislike();
    void Love();
};



#endif //POST_H
