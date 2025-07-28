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
    bool has_watched(const Film& film) const;
    const std::map<const Film*, Rating>& get_watched_history() const;
    std::string get_favorite_genre() const;

private:
    std::string username;
    std::map<const Film*, Rating> watched_history;
};

#endif 