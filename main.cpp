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
        cerr << "Not enough arguments provided (need at least 1 argument)." << "\n";
        cerr << "Usage: " << argv[ 0 ] << " moviesFilename prefixFilename " << "\n";
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
                cout << i->getMovieName() << ", " << i->getMovieRating() << "\n";
            }
            return 0;
    }

    ifstream prefixFile (argv[2]);

    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2];
        exit(1);
    }

    vector<string> prefixes; // S(m)
    while (getline (prefixFile, line)) { // O(m)
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }

    unordered_map<string, set<Movie, CompareByRating>> dict; // S(m + n), assuming that one movie won't overlap with multiple 
    
    //  For each prefix,
    //  Find all movies that have that prefix and store them in an appropriate data structure
    //  If no movie with that prefix exists print the following message
    for (int i = 0; i < prefixes.size(); i++) { // loop is O(m)
        string prefix = prefixes[i];

        auto it = s.lower_bound(Movie(prefix)); // set::lower_bound is O(log(n))
        if (it == s.end() || !isValidPrefix(prefix, it->getMovieName())) { //isValidPrefix is O(l)
            cout << "No movies found with prefix "<< prefix << "\n";
            continue;
        }

        while (1) { // dictionary insert loop is O(k)
            dict[prefix].insert(*it); // O(log(n))

            it++;

            if (it == s.end() || !isValidPrefix(prefix, it->getMovieName())) break; // isValidPrefix is O(l) 
        }

        for (auto i = dict[prefix].rbegin(); i != dict[prefix].rend(); i++) { // O(k)
            cout << i->getMovieName() << ", " << i->getMovieRating() << "\n";
        }

        cout << "\n";
    }

    //  For each prefix,
    //  Print the highest rated movie with that prefix if it exists.
    for (string p : prefixes) { // O(m)
        if (dict.find(p) == dict.end()) continue; // O(1)

        auto it = dict[p].rbegin();
        cout << "Best movie with prefix " << p << " is: " << it->getMovieName() << " with rating " << std::fixed << std::setprecision(1) << it->getMovieRating() << "\n";
    }

    return 0;
}

/* Add your run time analysis for part 3 of the assignment here as commented block*/
/*
Part 3a:
Going through each major series of operations:
The first prefix loop goes through every prefix and is O(m).
The second loop goes through every prefix and is O(m). 
Inside the loop: 
set::lower_bound is O(log(n))
isValidPrefix is O(l)
dictionary insert loop is O(k); within the loop, isValidPrefix is O(l) and the insert is O(log(k))
The third loop runs in O(m) time as well as it goes through every prefix.

In total, this is:
O(m + m*(log(n) + l+ k*(l+log(k)) + m)
O(mlog(n) + ml + mklog(k) + mkl + m)
The final m can be dropped as it is lower order. The ml term cannot be dropped because k could be 0. 
O(mlog(n) + ml + mk(log(k) + l))
-----------
The runtime for each input file:
input_20_random.csv - 224 ms
input_100_random.csv - 303 ms
input_1000_random.csv - 326 ms
input_76290_random.csv - 1860 ms
*/
/*
Part 3b:
The two axillary data structures used in my algorithm for part 2 are the vector of prefixes and the diuctionary of prefix, movie set pairs. 
The vector is S(m) because it contains the m prefixes.
The dictionary contains at most all m dictionaries and all n movies (assuming movies uniquely match to one single prefix). This is S(n + m)
This is results at S(n + 2m) -> S(n + m).
*/
/*
Part 3c:
I tried to design my algorithm with a low time complexity in mind. My primary goal was to avoid any O(n^2/m^2/mn) time complexity. 
In my opinion, I achieved this goal, which was reflected in both my time complexity analysis and my extremely low runtime on the 76920 random input set.
I find this especially apparent in the fact that I did not simply loop through every movie for each prefix, but used the set::lower_bound function to reduce operations.
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