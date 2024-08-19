#include <string>

class User {
private:
    const string id;
    const string name;
    const string email;

public:
    User(const string& id, const string& name, const string& email)
        : id(id), name(name), email(email) {}
};

