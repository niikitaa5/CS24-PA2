// movies.h
// name and date

#ifndef MOVIES_H
#define MOVIES_H

#include <iostream>
#include <string>
#include <string.h>

using namespace std;

class Movie {
    public:
        Movie(string n, double r);
        string getName() const;
        double getRating() const;
        void setName(string n);
        void setRating(double r);
        //bool operator<(const Movie &a);

    private:
        string name;
        double rating;
};

class cmpMovie{
 public:
    bool operator()(const Movie &a, const Movie &b) const;
};

class cmpRating{
 public:
    bool operator()(const Movie &a, const Movie &b) const;
};


#endif