// movies.h
// Author: Zach Miller

#ifndef MOVIES_H
#define MOVIES_H

#include <string>

class Movie{
    public:
        Movie() : movieName(""), movieRating(0) {} // For the hashmap
        Movie(std::string name) : movieName(name), movieRating(0) {} // For searching
        Movie(std::string name, double rating) : movieName(name), movieRating(rating) {} 
        std::string getMovieName() const;
        double getMovieRating() const;
        bool operator>(const Movie& other) const;
        bool operator<(const Movie& other) const;
    private:
        std::string movieName;
        double movieRating; 
};

#endif