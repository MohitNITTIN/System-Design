#include <string>
#include <vector>


class Show; // Forward declaration of Show class

class Theater {
private:
    const string id;
    const string name;
    const string location;
    const vector<Show> shows;

public:

    Theater(const string& id, const string& name, const string& location, const vector<Show>& shows)
        : id(id), name(name), location(location), shows(shows) {}
};

