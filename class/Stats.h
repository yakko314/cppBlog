//
// Created by lam on 18.05.2025.
//

#ifndef STATS_H
#define STATS_H



class Stats {
    unsigned int like;
    unsigned int dislike;
    unsigned int love;
public:
    Stats();
    void Like();
    void Dislike();
    void Love();

    unsigned int getLike() const{ return like;}
    unsigned int getDislike() const{ return dislike;}
    unsigned int getLove() const{ return love;}
};

#endif //STATS_H
