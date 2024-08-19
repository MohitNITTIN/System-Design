#include<bits/stdc++.h>
#include <string>
#include <map>
#include <chrono>
using namespace std;

class Movie; // Forward declaration
class Theater; // Forward declaration
class Seat; // Forward declaration

class Show {
private:
    const string id;
    const Movie* movie;
    const Theater* theater;
    const chrono::system_clock::time_point startTime;
    const chrono::system_clock::time_point endTime;
    const map<string, Seat> seats;

public:
    Show(const string& id, const Movie* movie, const Theater* theater, 
         const chrono::system_clock::time_point& startTime, 
         const chrono::system_clock::time_point& endTime, 
         const map<string, Seat>& seats)
        : id(id), movie(movie), theater(theater), 
          startTime(startTime), endTime(endTime), seats(seats) {}

    string getId() const {
        return id;
    }

    const Movie* getMovie() const {
        return movie;
    }

    const Theater* getTheater() const {
        return theater;
    }

    chrono::system_clock::time_point getStartTime() const {
        return startTime;
    }

    chrono::system_clock::time_point getEndTime() const {
        return endTime;
    }

    const map<string, Seat>& getSeats() const {
        return seats;
    }
};

