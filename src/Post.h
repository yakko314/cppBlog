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

/**
 * @class Post
 * @brief O postare.
 */
class Post {
    int id; ///< identificatorul intern al unei postari
    string title; ///< titlul unei postari
    string file; ///< fisierul asociat unei postari, NULL sau [<name>(.jpg)|(.mp3)|(.mp4)]
    string content; ///< continutul text al unei postari
    vector<Comment> comments; ///< totalul de comentarii al unei postari
    Stats stats; ///< contine totalul de interactiuni ale unei postari
    Date date; ///< data postarii
public:
    /**
     * @brief Constructor pentru postare
     * @param id identificator intern
     * @param title titlu
     * @param file fisier atasat sau NULL
     * @param content continut text
     * @param date data postarii
     */
    Post(const int& id, const string& title, const string& file, const string& content, const Date& date);
    /**
     * @brief Adauga un like postarii.
     */
    void Like();
    /**
     * @brief Adauga un dislike postarii.
     */
    void Dislike();
    /**
     * @brief Adauga un love postarii.
     */
    void Love();
    void setStats(const Stats& stats){this->stats = stats;}

    /**
     * @brief Supraincarca operatorul de afisare, afiseaza postari "compact", fara continut si comentarii.
     * @param os streamul care va fi creat
     * @param post Postarea care vrem sa afisam, pe scurt
     * @return o referinta la stream
     */
    friend ostream& operator<<(ostream& os, const Post& post);

    /**
     * O noua functie pentru afisarea unei postari in intregime, cu continut si comentarii.
     * @param os streamul care va fi folosit
     */
    void bigPrint(std::ostream& os) const;

    /**
     * Adauga un comentariu unei postari
     * @param comment comentariul care va fi adaugat
     */
    void addComment(const Comment& comment);

    /**
     * O functie pentru afisarea comentariilor pentru o anumita postare
     * @param os streamul care va fi folosit
     */
    void commentPrint(std::ostream&os) const;

    /**
     * O functie pentru afisarea interactiuniilor pentru o anumita postare
     * @param os streamul care va fi folosit
     */
    void interactionPrint(std::ostream&os) const;

    /**
     * O functie pentru a edita continutul unei postari
     * @param newcontent este continutul nou pentru postare
     */
    void editcontent(string newcontent){this->content=newcontent;}

    vector<Comment> getComments() const { return comments;};
    int getId()const{ return id;}
    Stats getStats() const { return stats;}
    string getTitle() const{return title;}
    string getFile() const{return file;}
    string getContent() const{return content;}
    Date getDate() const{return date;}
};



#endif //POST_H
