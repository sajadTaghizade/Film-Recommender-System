#ifndef USER_H
#define USER_H

#include "includes.h"
#include "Film.h"
#include "Rating.h"

class User {
public:
    User(const std::string& username);

    void add_watched_film(const Film* film, Rating rating);
    std::string get_username() const;

private:
    std::string username;
    std::map<const Film*, Rating> watched_history;
};

#endif 