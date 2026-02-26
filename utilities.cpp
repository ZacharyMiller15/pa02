#include "utilities.h"

bool isValidPrefix(const std::string& prefix, const std::string& word) {
    if (prefix.length() > word.length()) return false;

    return word.compare(0, prefix.size(), prefix) == 0;
}

bool CompareByRating::operator()(const Movie& a, const Movie& b) const {
    if (a.getMovieRating() == b.getMovieRating()) return a.getMovieName() > b.getMovieName();
    return a.getMovieRating() < b.getMovieRating();
}