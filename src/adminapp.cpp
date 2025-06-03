#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

#include "Comment.h"
#include "Post.h"

using namespace std;

ifstream f;


vector<Post> posts;
unordered_map<int, int> idToIndex;

void read() {

    f.open("tests/Postari.txt");
    int n;
    f >> n;
    for (int i = 0; i < n; i++) {
        int id;
        string title;
        string file;
        string content;
        f >> id;
        f.ignore();
        getline(f, title);
        getline(f, file);
        getline(f, content);
        idToIndex[id] = posts.size();

        int day;
        int month;
        int year;
        f >> day >> month >> year;

        Date date(day,month,year);
        Post post(id,title,file,content,date);

        posts.push_back(post);
    }
    f.close();

    f.open("tests/Comentarii.txt");
    string content;
    f >> n;
    for (int i = 0; i < n; i++) {
        int x;
        f>>x;
        f.ignore();
        string username;
        getline(f, username);
        getline(f, content);
        int day, month, year;
        f >> day >> month >> year;
        if (idToIndex.count(x)) {
            Date date(day,month,year);
            Comment comment(username,content,date);
            // std::cout << "Adding comment to post " << x << ": \"" << content << "\" by " << username << " on " << date << "\n";
            posts[idToIndex[x]].addComment(comment);
        }
    }

    f.close();

    f.open("tests/Statistici.txt");
    f >> n;
    for (int i = 0; i < n; i++) {
        int x;
        f>>x;
        if (idToIndex.count(x)) {
            int like, dislike, love;
            f >> like >> dislike >> love;
            Stats stats(like,dislike,love);
            posts[idToIndex[x]].setStats(stats);

        } else {
            unsigned int tmp1, tmp2, tmp3;
            f >> tmp1 >> tmp2 >> tmp3;
        }
    }
    f.close();

}

void showAll() {
    for (auto const &p : posts) {
        cout << p << '\n';
    }
}
void showAllExpanded() {
    for (auto& p : posts) {
        // cout << p << '\n';
        // // for (const auto& c : p.getComments()) {
        // //     cout << c << '\n';
        // // }
        p.bigPrint(cout);
        cout << '\n';
    }
}

int main() {
    read();
    showAll();
    showAllExpanded();
    return 0;
}
