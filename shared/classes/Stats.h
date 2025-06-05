//
// Created by lam on 18.05.2025.
//

#ifndef STATS_H
#define STATS_H
#include <iostream>

/**
 * @class Stats
 * @brief Contine interactiuni, contor pentru like, dislike si love.
 */
class Stats {
    unsigned int like;
    unsigned int dislike;
    unsigned int love;
public:
    /**
     * @brief Constructor default pentru interactiuni, va da valorile de 0, 0, 0.
     */
    Stats();

    /**
     * Constructor pentru interactiuni, va asocia valorile date cu like, dislike, love.
     * @param like
     * @param dislike
     * @param love
     */
    Stats(unsigned int like, unsigned int dislike, unsigned int love);

    /**
     * @brief Adauga un like in interactiuni.
     */
    void Like();

    /**
     * @brief Adauga un dislike in interactiuni.
     */
    void Dislike();

    /**
     * @brief Adauga un love in interactiuni.
     */
    void Love();

    /**
     * @brief Supraincarca operatorul de afisare
     * @param os streamul care va fi creat
     * @param stats Interactiunile care vrem sa afisam in intregime
     * @return o referinta la stream
     */
    friend std::ostream& operator<<(std::ostream& os, const Stats& stats);

    void setStats(const Stats& stats) {this->like = stats.like; this->dislike = stats.dislike; this->love = stats.love;};
    unsigned int getLike() const{ return like;}
    unsigned int getDislike() const{ return dislike;}
    unsigned int getLove() const{ return love;}
};

#endif //STATS_H
