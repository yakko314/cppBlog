//
// Created by lam on 18.05.2025.
//

#include "Stats.h"

#define RESET   "\033[0m"
#define BLUE    "\033[34m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define CYAN    "\033[36m"

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
    os << GREEN << "+" << stats.like << RESET << " | "
    << CYAN << "-" << stats.dislike << RESET << " | "
    << RED << stats.love << " <3" << RESET;

    return os;
}
