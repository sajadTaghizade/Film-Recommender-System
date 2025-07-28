#include "User.h"
#include "constants.h"

User::User(const std::string& username) : username(username) {}

void User::add_watched_film(const Film* film, Rating rating) {
    watched_history[film] = rating;
}

std::string User::get_username() const {
    return username;
}

bool User::has_watched(const Film& film) const {
    for (const auto& pair : watched_history) {
        if (pair.first->get_name() == film.get_name()) {
            return true;
        }
    }
    return false;
}

const std::map<const Film*, Rating>& User::get_watched_history() const {
    return watched_history;
}

std::string User::get_favorite_genre() const {
    if (watched_history.empty()) {
        return "";
    }

    std::map<std::string, int> genre_counts;
    for (const auto& [film_ptr, rating] : watched_history) {
        genre_counts[film_ptr->get_genre()]++;
    }

    std::string favorite_genre = "";
    int max_count = 0;
    for (const auto& [genre, count] : genre_counts) {
        if (count > max_count) {
            max_count = count;
            favorite_genre = genre;
        }
    }
    return favorite_genre;
}