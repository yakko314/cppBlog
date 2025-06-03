#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

#include <chrono>
#include <ctime>


#include "Comment.h"
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


using namespace std;

ifstream f;
ofstream g;

vector<Post> posts;
unordered_map<int, int> idToIndex;

int nrPosts = 0;
int nrComments = 0;
void read() {

    f.open("tests/Postari.txt");
    f >> nrPosts;
    for (int i = 0; i < nrPosts; i++) {
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
    f >> nrComments;
    for (int i = 0; i < nrComments; i++) {
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
    int nrInteractiuni;
    f >> nrInteractiuni;
    for (int i = 0; i < nrInteractiuni; i++) {
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
    int i = 1;
    for (auto const &p : posts) {
        cout << i++ << " | " << p << '\n';
    }
}
void showAllExpanded() {
    for (auto& p : posts) {
        p.bigPrint(cout);
        cout << '\n';
    }
}

void cmdHelp() {
    cout << CYAN "~Sistem de blog: Admin~\n" RESET
    << GREEN "etc" RESET "- etcetcetc";
}
void noPost() {
    cout << RED "Postarea nu exista!\n" RESET;
}

int main(int argc, char* argv[]){
    read();
    if (argc == 1) {
        cmdHelp();
        return 0;
    }
    string command = argv[1];
    if (command == "etcetc") {

    }
}
