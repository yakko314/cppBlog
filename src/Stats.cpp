//
// Created by lam on 18.05.2025.
//

#include "Stats.h"

Stats::Stats() : like(0), dislike(0), love(0) {
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

