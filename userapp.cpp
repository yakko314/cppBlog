#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

#include <chrono>
#include <ctime>


#include "shared/classes/Comment.h"
#include "shared/classes/Post.h"

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

vector<Post> posts; ///< Toate postarile de pe blog.
unordered_map<int, int> idToIndex; ///< Un map pe care il folosim pentru a face conversia din ID in index din lista

int nrPosts = 0; ///< variabila ajutatoare pentru nr de postari
int nrComments = 0; ///< variabila ajutatoare pentru nr de comentarii
/**
 * @brief Citeste toate datele relevante si le include in clase cu care putem lucra
 */
void read() {

    f.open("shared/files/Postari.txt");
    if (!f) {
        cerr << RED "Nu exista fisierul cu " MAGENTA "postari" RED "! Datele afisate pot fi gresite!\n" RESET;
        return;
    }
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

    f.open("shared/files/Comentarii.txt");
    if(!f) {
        cerr << RED "Nu exista fisierul cu " YELLOW "comentarii" RED "! Datele afisate pot fi gresite!\n" RESET;
        return;
    }    string content;
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

    f.open("shared/files/Statistici.txt");
    if(!f) {
        cerr << RED "Nu exista fisierul cu " GREEN "interactiuni" RED "! Datele afisate pot fi gresite!\n" RESET;
        return;
    }    int nrInteractiuni;
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

/**
 * @brief Scrie interactiuni catre fisierul ce le contine
 */
void writeToStats() {
    int nrInteractiuni = 0;
    for (const auto& p : posts) {
        if (p.getStats().getLike() != 0 ||
            p.getStats().getDislike() != 0 ||
            p.getStats().getLove() != 0) {
            nrInteractiuni++;
            }
    }
    g.open("shared/files/Statistici.txt");
    g << nrInteractiuni << "\n\n";
    for (const auto& p : posts) {
        if (p.getStats().getLike() != 0 || p.getStats().getDislike() != 0 || p.getStats().getLove() != 0) {
            g << p.getId() << '\n';
            g << p.getStats().getLike() << ' '
            << p.getStats().getDislike() << ' '
            << p.getStats().getLove() << '\n';
            g << '\n';
        }

    }
    g.close();
}

/**
 * @brief Scrie comentarii catre fisierul care le contine
 */
void writeToComments() {
    g.open("shared/files/Comentarii.txt");
    g << nrComments << "\n\n";
    for (const auto& p : posts) {
        if (!p.getComments().empty()) {
            for (const auto& c : p.getComments()) {
                g << p.getId() << '\n';
                g << c.getUsername() << '\n';
                g << c.getContent() << '\n';
                g << c.getDate().getDay() << ' ';
                g << c.getDate().getMonth() << ' ';
                g << c.getDate().getYear() << '\n';
                g << "\n";
            }

        }
    }
    g.close();
}

/**
 * O functie care verifica daca sa introdus un numar natrual pozitiv
 * @param s este variabila care se verifica
 */
bool isPositive(string s){
    if(s.empty()) 
        return false;
    if(s[0]=='+'){
        if(s.size()==1)
            return false;
    }
    else{
        if(!isdigit(s[0]) || s[0]=='-')
            return false;
    }
    for(int i=1;i<s.size();i++){
        if(!isdigit(s[i]))
            return false;
    }
    return true;
}

/**
 * @brief Afiseaza toate postarile in mod compact.
 */
void showAll() {
    int i = 1;
    for (auto const &p : posts) {
        cout << i++ << " | " << p << '\n';
    }
}

/**
 * @brief Afiseaza toate postarile cu continut si comentarii, a fost folosita doar in testare.
 */
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

/**
 * @brief Afiseaza toate comenzile posibile
 */
void cmdHelp() {
    cout << CYAN "~Sistem de blog: Utilizator~\n" RESET
    << GREEN "vizualizare_postari" RESET " - arata toate postarile intr-o lista numerotata;\n"
    << GREEN "vizualizare_postare <nr_postare>" RESET " - arata o postare in detaliu (continut + comentarii);\n"
    << GREEN "adauga_comentariu <nr_postare> <username> <continut_comentariu> " RESET "- adauga un comentariu unei postari, va rugam sa folosititi citate pentru username si continut;\n"
    << GREEN "adauga_interactiune <nr_postare> <like|dislike|love> " RESET "- adauga o anume interactiune unei postari.";
}

/**
 * @brief Semnaleaza lipsa unei postari la un anume index.
 */
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
    if (command == "help") {
        cmdHelp();
        return 0;
    }
    if (command == "vizualizare_postari") {
        showAll();
        return 0;
    }
    if (command == "vizualizare_postare") {
        if(argc < 3 || argc > 3){
            cout<< GREEN "Utilizare: " RESET "vizualizare_postare <nr_postare>\n";
            return 0;
        }
        string s=argv[2];
        if(!isPositive(s)){
            cout<<RED "<nr_postare>" RESET " trebuie sa fie un numar natural pozitiv.\n";
            cout<< GREEN "Utilizare: " RESET "vizualizare_postare <nr_postare>\n";
            return 0;
        }
        int index = stoi(argv[2]) - 1;
        if (index >= 0 && index < posts.size()) {
            posts[index].bigPrint(cout);
        }
        else {
            noPost();
        }
        return 0;
    }
    if (command == "adauga_comentariu") {
        if (argc < 5 || argc > 5) {
            cerr << GREEN "Utilizare: " RESET "adauga_comentariu <nr_postare> <username> <continut_comentariu>\n";
            return 0;
        }

        //Extragem data curenta
        auto now = chrono::system_clock::now();
        time_t now_time = chrono::system_clock::to_time_t(now);
        tm* local_tm = localtime(&now_time);
        int day = local_tm->tm_mday;
        int month = local_tm->tm_mon + 1;
        int year = local_tm->tm_year + 1900;

        //cout << day << "." << month << "." << year << '\n';
        Date date(day,month,year);
        string s=argv[2];
        if(!isPositive(s)){
            cerr<<RED "<nr_postare>" RESET " trebuie sa fie un numar natural pozitiv.\n";
            cerr << GREEN "Utilizare: " RESET "adauga_comentariu <nr_postare> <username> <continut_comentariu>\n";
            return 0;
        }
        int index = stoi(argv[2]) - 1;
        if (index >= 0 && index < posts.size()) {
            string username = argv[3];
            string content = argv[4];
            Comment comment(username,content,date);
            posts[index].addComment(comment);
            cout << YELLOW "Comentariu " RESET "s-a adaugat cu success!\n";

            nrComments++;
            //posts[index].bigPrint(cout);

            writeToComments();
        }
        else noPost();
        return 0;
    }
    if (command == "adauga_interactiune") {
        if (argc < 4 || argc > 4) {
            cerr << GREEN "Utilizare:" RESET " adauga_interactiune <nr_postare> <like|dislike|love>\n";
            return 0;
        }
        string s=argv[2];
        if(!isPositive(s)){
            cerr<<RED "<nr_postare>" RESET " trebuie sa fie un numar natural pozitiv.\n";
            cerr << GREEN "Utilizare:" RESET " adauga_interactiune <nr_postare> <like|dislike|love>\n";
            return 0;
        }
        int index = stoi(argv[2]) - 1;
        if (index >= 0 && index < posts.size()) {
            string interaction = argv[3];
            if (interaction == "like") posts[index].Like(), cout << GREEN "Like";
            else if (interaction == "dislike") posts[index].Dislike(), cout << CYAN "Dislike";
            else if (interaction == "love") posts[index].Love(), cout << RED "Love";
            else {
                cerr<<RED "Trebuie introdus like, dislike sau love pentru a adauga o interactiune\n" RESET;
                return 0;
            }
            cout << RESET " s-a adaugat cu success!\n";
            writeToStats();
        }
        else noPost();
        return 0;
    }
    cout<<RED<<"Comanda nu exista!\n"<<RESET << "Foloseste comanda " GREEN "help" RESET " pentru comenzile disponibile.\n";
}
