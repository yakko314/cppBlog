#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "Post.h"

using namespace std;

ifstream f;

// struct Stats {
//     unsigned int like = 0;
//     unsigned int dislike = 0;
//     unsigned int love = 0;
// };
//
// struct Post {
//     int id;
//     string s;
//     string file;
//     string content;
//     vector<string> comments;
//     Stats stat;
// };

//placeholder read and write code to verify eveyrthing works

vector<Post> posts;
unordered_map<int, int> idToIndex;


void read() {

    f.open("dummyInputs/Postari.txt");
    int n;
    f >> n;
    for (int i = 0; i < n; i++) {
        Post post;
        f >> post.id;
        f.ignore();
        getline(f, post.title);
        getline(f, post.file);
        getline(f, post.content);
        idToIndex[post.id] = posts.size();
        posts.push_back(post);
    }
    f.close();

    f.open("dummyInputs/Comentarii.txt");
    int x;
    string s;
    while (f >> x) {
        f.ignore();
        getline(f, s);
        if (idToIndex.count(x)) {
            posts[idToIndex[x]].comments.push_back(s);
        }
    }

    f.close();

    f.open("dummyInputs/Statistici.txt");
    while (f >> x) {
        if (idToIndex.count(x)) {
            auto& stat = posts[idToIndex[x]].stat;
            f >> stat.like >> stat.dislike >> stat.love;
        } else {
            unsigned int tmp1, tmp2, tmp3;
            f >> tmp1 >> tmp2 >> tmp3;
        }
    }
    f.close();

}

void Show() {
    for (const auto& post : posts) {
        cout << post.id << '|' << post.s << '\n' << post.file << '\n' << post.comments.size() << "💬|";

        cout << post.stat.like << "👍 | " << post.stat.dislike << "👎 | " << post.stat.love << "❤️\n";
        for (const auto& c : post.comments)
            cout << c << '\n';
    }
}

int main() {
    read();
    Show();
    return 0;
}
