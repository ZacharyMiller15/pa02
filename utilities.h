#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include "movies.h"

bool isValidPrefix(const std::string& prefix, const std::string& word);

struct CompareByRating {
    bool operator()(const Movie& a, const Movie& b) const;
};

#endif