#ifndef RECOMMENDER_H
#define RECOMMENDER_H

#include "includes.h"
#include "Film.h"
#include "User.h"

class Recommender {
public:
    void run();

private:
    void load_data(const std::string& films_path, const std::string& users_path);
    void process_commands();
    void handle_genre_recommendation(const std::vector<std::string>& args);
    void read_films(const std::string& file_path);
    void read_users(const std::string& file_path);
    std::vector<Film> films;
    std::vector<User> users;
    std::map<std::string, const User*> user_lookup; 
};

#endif
