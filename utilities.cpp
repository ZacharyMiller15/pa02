#include "utilities.h"

bool isValidPrefix(std::string prefix, std::string word) {
    if (prefix.length() > word.length()) return false;

    if (prefix == word || word.substr(0, prefix.length()) == prefix) return true;

    return false;
}

bool CompareByRating::operator()(const Movie& a, const Movie& b) const {
    if (a.getMovieRating() == b.getMovieRating()) return a.getMovieName() > b.getMovieName();
    return a.getMovieRating() < b.getMovieRating();
}