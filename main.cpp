// Spring'22
// Instructor: Diba Mirza
// Student name: 

#include "movies.h"

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
#include <string.h>
#include <unordered_set>

using namespace std;

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
    //cmp comp;
    set<Movie, cmpMovie> movieSet;
    string line, movieName;
    double movieRating;
    // Read each file and store the name and rating
    while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
            // Use std::string movieName and double movieRating
            // to construct your Movie objects
            // cout << movieName << " has rating " << movieRating << endl;
            // insert elements into your data structure
        Movie obj(movieName, movieRating);
        //cout << movieName << " has rating " << movieRating << endl;
        movieSet.insert(obj);
        
    }
    movieFile.close();

    if (argc == 2){
        for(auto i : movieSet)
            cout << i.getName() << ", " << i.getRating() << endl;
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

//     //  For each prefix,
//     //  Find all movies that have that prefix and store them in an appropriate data structure
//     //  If no movie with that prefix exists print the following message
//     cout << "No movies found with prefix "<<"<replace with prefix>" << endl << endl;


    vector<set<Movie, cmpRating>> movieVec;
    queue<Movie> highestRated;
    bool check;

    for (const auto& p : prefixes) {
        int length = p.size();
        set<Movie, cmpRating> temp;
        movieVec.emplace_back(temp);

        Movie lower(p, 0.0);
        auto it = movieSet.lower_bound(lower);

        while ((it != movieSet.end()) and (it->getName().compare(0, length, p) == 0)) {
                temp.insert(*it);
                it++;
        }

        if (temp.empty()) {
            cout << "No movies found with prefix "<< p;
            Movie m("\0", 0.0);
            highestRated.emplace(m);
        }
        else {
            check = true;
            for (const auto& i : temp) {
                cout << i.getName() << ", " << i.getRating() << endl;
                if (check) {
                    highestRated.emplace(i);
                    check = false;
                }
            }
        }
    cout << endl;
    }


    int i = 0;
    for (auto p : prefixes) {
        if (highestRated.front().getName() != "\0") {
            cout << "Best movie with prefix " << p << " is: " << highestRated.front().getName()
                 << " with rating " << highestRated.front().getRating() << endl;
        }
        highestRated.pop();
        i++;
    }
}
    

   
 

    // vector<priority_queue<Movie, vector<Movie>, cmpRating>> movieVec;
    // queue<Movie> highestRated;
    // for (auto p : prefixes) {
    //     int length = p.size();
    //     priority_queue<Movie, vector<Movie>, cmpRating> temp;
    //     movieVec.push_back(temp);
    //     for (auto m : movieSet) {
    //         if (m.getName().substr(0,length) == p)
    //             temp.push(m);
    //     }

    //     if (!temp.empty())
    //         highestRated.emplace(temp.top());
    //     else {
    //         Movie m("\0", 0.0);
    //         highestRated.emplace(m);
    //     }

    //     if (temp.empty())
    //         cout << "No movies found with prefix "<< p;
    //     else {
    //         while (!temp.empty()) {
    //             cout << temp.top().getName() << ", " << temp.top().getRating() << endl;
    //             temp.pop();
    //         }
    //     }
    //     cout << endl;
    // }




    // for (auto p : prefixes) {
    //     if (highestRated.front().getName() != "\0")
    //         cout << "Best movie with prefix " << p << " is: " 
    //              << highestRated.front().getName() << " with rating " << highestRated.front().getRating() << endl;
    //     highestRated.pop();
    // }

    //cout << "hehe done" << endl;

    // for (auto i : movieVec) {
    //     cout << "hey" << endl;
    //     cout << i.top().getName() << " " << i.top().getRating() << endl;
    //}

    // int count = 0;
    // while (!highestRated.empty()) {
    //     cout << "Best movie with prefix " << prefixes[count] << " is: " 
    //          << highestRated.front().getName() << " with rating " << highestRated.front().getRating() << endl;
    //     highestRated.pop();
    //     count++;
    // }


    //unordered_set<Movie> finalMovies;













//     //  For each prefix,
//     //  Print the highest rated movie with that prefix if it exists.
//     cout << "Best movie with prefix " << "<replace with prefix>" << " is: " << "replace with movie name" << " with rating " << std::fixed << std::setprecision(1) << "replace with movie rating" << endl;

//     return 0;
 //}

// /* Add your run time analysis for part 3 of the assignment here as commented block*/

bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
 }



  // priority_queue<Movie, vector<Movie>, cmpRating> movieQueue;

    // for (auto i : prefixes) {
    //     int length = i.size();
    //     int countPre = 0;
    //     for (auto j : movieSet) {
    //         if (j.getName().substr(0,length) == i) {
    //             movieQueue.push(j);
    //             //cout << j.getName() << " " << j.getRating() << endl;
    //             countPre++;
    //         }
    //     }
    //     if (countPre == 0)
    //         cout << "No movies found with prefix "<< i << endl << endl;
    // }

    // while (!movieQueue.empty()) {
    //     Movie m = movieQueue.top();
    //     cout << m.getName() << " " << m.getRating() << endl;
    //     movieQueue.pop();
    // }