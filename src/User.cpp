#include "User.h"
#include "constants.h"

User::User(const std::string& username) : username(username) {}

void User::add_watched_film(const Film* film, Rating rating) {
    watched_history[film] = rating;
}

std::string User::get_username() const {
    return username;
}