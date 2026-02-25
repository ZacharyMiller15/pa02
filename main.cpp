// Winter'26
// Instructor: Diba Mirza
// Student name: Zach Miller
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
#include <sstream>
#include <unordered_map>
using namespace std;

#include "utilities.h"
#include "movies.h"

bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){
    if (argc < 2){
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[ 0 ] << " moviesFilename prefixFilename " << endl;
        exit(1);
    }

    ifstream movieFile (argv[1]);
 
    if (movieFile.fail()){
        cerr << "Could not open file " << argv[1];
        exit(1);
    }
  
    // Create an object of a STL data-structure to store all the movies

    string line, movieName;
    double movieRating;
    set<Movie> s;
    // Read each file and store the name and rating
    while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
            // Use std::string movieName and double movieRating
            // to construct your Movie objects
            Movie m = Movie(movieName, movieRating);
            //cout << m.getMovieName() << " has rating " << m.getMovieRating() << endl;
            // insert elements into your data structure
            s.insert(m);
    }

    movieFile.close();

    if (argc == 2){
            //print all the movies in ascending alphabetical order of movie names
            for (auto i = s.begin(); i != s.end(); ++i) {
                cout << i->getMovieName() << ", " << i->getMovieRating() << endl;
            }
            return 0;
    }

    ifstream prefixFile (argv[2]);

    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2];
        exit(1);
    }

    vector<string> prefixes;
    while (getline (prefixFile, line)) {
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }

    unordered_map<string, set<Movie, CompareByRating>> dict;
    
    //  For each prefix,
    //  Find all movies that have that prefix and store them in an appropriate data structure
    //  If no movie with that prefix exists print the following message
    for (int i = 0; i < prefixes.size(); i++) {
        string prefix = prefixes[i];

        auto it = s.lower_bound(Movie(prefix));
        if (it == s.end() || !isValidPrefix(prefix, it->getMovieName())) {
            cout << "No movies found with prefix "<< prefix << endl;
            continue;
        }

        while (1) {
            dict[prefix].insert(*it);

            it++;

            if (it == s.end() || !isValidPrefix(prefix, it->getMovieName())) break;
        }

        for (auto i = dict[prefix].rbegin(); i != dict[prefix].rend(); i++) {
            cout << i->getMovieName() << ", " << i->getMovieRating() << endl;
        }
    }

    cout << endl;
    
    //  For each prefix,
    //  Print the highest rated movie with that prefix if it exists.
    for (string p : prefixes) {
        if (dict.find(p) == dict.end()) continue;

        auto it = dict[p].rbegin();
        cout << "Best movie with prefix " << p << " is: " << it->getMovieName() << " with rating " << std::fixed << std::setprecision(1) << it->getMovieRating() << endl;
    }

    return 0;
}

/* Add your run time analysis for part 3 of the assignment here as commented block*/
/*
Part 3a:
The time complexity is O().

Part 3b:
The space complexity is O().
*/

bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}