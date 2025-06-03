//
// Created by lam on 18.05.2025.
//

#include "Stats.h"
using namespace std;

Stats::Stats() : like(0), dislike(0), love(0) {
}

Stats::Stats(unsigned int like, unsigned int dislike, unsigned int love)
    : like(like), dislike(dislike), love(love) {

}

void Stats::Like() {
    like++;
}

void Stats::Dislike() {
    dislike++;
}

void Stats::Love() {
    love++;
}

std::ostream & operator<<(std::ostream &os, const Stats &stats) {
    os << stats.like << "👍 | " << stats.dislike << "👎 | " << stats.love << "❤️";
    return os;
}
