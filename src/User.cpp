#include "User.h"
#include "constants.h"

User::User(const std::string& username) : username(username) {}

void User::add_watched_film(const Film* film, Rating rating) {
    watched_history[film] = rating;
}

void User::print() const {
    std::cout << "Username: " << username << std::endl;
    std::cout << "  Watched Films:" << std::endl;
    for (const auto& pair : watched_history) {
        std::cout << "    - " << pair.first->get_name() 
                  << " (Rated: " << rating_to_string(pair.second) << ")" << std::endl;
    }
}