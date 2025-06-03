//
// Created by lam on 18.05.2025.
//

#ifndef STATS_H
#define STATS_H
#include <iostream>


class Stats {
    unsigned int like;
    unsigned int dislike;
    unsigned int love;
public:
    Stats();
    Stats(unsigned int like, unsigned int dislike, unsigned int love);

    void Like();
    void Dislike();
    void Love();

    friend std::ostream& operator<<(std::ostream& os, const Stats& stats);

    void setStats(const Stats& stats) {this->like = stats.like; this->dislike = stats.dislike; this->love = stats.love;};
    unsigned int getLike() const{ return like;}
    unsigned int getDislike() const{ return dislike;}
    unsigned int getLove() const{ return love;}
};

#endif //STATS_H
