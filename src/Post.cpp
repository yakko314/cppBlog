//
// Created by lam on 18.05.2025.
//

#include "Post.h"

Post::Post(const string& title, const string& file, const string& content)
    : title(title), file(file), content(content) {
    id = 0;
}

void Post::Like() {
    stats.Like();
}

void Post::Dislike() {
    stats.Dislike();
}

void Post::Love() {
    stats.Love();
}

