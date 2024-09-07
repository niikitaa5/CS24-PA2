// movies.cpp
// Implements class movies
// name
// date

#include "movies.h"

#include <iostream>

using namespace std;

Movie::Movie(string n, double r) {
    rating = r;
    name = n;
}

string Movie::getName() const{
    return name;
}

double Movie::getRating() const {
    return rating;
}
    
void Movie::setName(string n){
    name = n;
}

void Movie::setRating(double r){
    rating = r;
}

// bool Movie::operator< (const Movie &a){
//     int index = 0;
//     while (getName()[index] == a.getName()[index]) 
//        index++;
//     return (getName()[index] < a.getName()[index]);
// }
    
bool cmpMovie::operator()(const Movie &a, const Movie &b) const{ // returns the lesser movie object
    int index = 0;
    while (a.getName()[index] == b.getName()[index]) 
        index++;
    return (a.getName()[index] < b.getName()[index]);
}

bool cmpRating::operator()(const Movie &a, const Movie &b) const{ // returns the higher rated movie
    if (a.getRating() == b.getRating()) {
        cmpMovie movCompare;
        return movCompare(a, b);
    }
    return (a.getRating() > b.getRating());

}



// int main(){
//     cout << "hello" << endl;
// }
    