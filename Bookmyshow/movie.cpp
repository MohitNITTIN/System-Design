#include <bits/stdc++.h>
using namespace std;


class Movie
{
public:
    Movie(const string &id, const string &title, const string &description, int durationInMinutes) 
    : id(id), title(title), description(description), durationInMinutes(durationInMinutes) {}

    int getDurationInMinutes() const { return durationInMinutes; }

private:
    string id;
    string title;
    string description;
    int durationInMinutes;
};