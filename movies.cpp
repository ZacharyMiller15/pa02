#include "movies.h"

std::string Movie::getMovieName() const {
    return movieName;
}

double Movie::getMovieRating() const {
    return movieRating;
}

bool Movie::operator>(const Movie& other) const {
    return this->movieName > other.getMovieName();
}

bool Movie::operator<(const Movie& other) const {
    return this->movieName < other.getMovieName();
}