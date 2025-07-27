#include "Recommender.h"
#include "utils.h"
#include "constants.h"
#include "Rating.h"
#include "IScoringStrategy.h"
#include "includes.h"

class HistoryScorer;
class GenericScorer;


void Recommender::run() {
    load_data("files/films.csv", "files/users.csv");
    process_commands();
}

void Recommender::load_data(const std::string& films_path, const std::string& users_path) {
    read_films(films_path);
    read_users(users_path);

    for (const auto& user : users) {
        user_lookup[user.get_username()] = &user;
    }
}

void Recommender::process_commands() {
    std::string line;
    while (std::getline(std::cin, line)) {
        std::vector<std::string> tokens = split(line, SPACE);
        if (tokens.empty() || tokens[0].empty()) continue;

        const std::string& command = tokens[0];

        
        std::vector<std::string> args(tokens.begin() + 1, tokens.end());

        for (auto& arg : args) {
            if (!arg.empty() && arg.front() == '"' && arg.back() == '"') {
                arg = arg.substr(1, arg.length() - 2);
            }
        }

        if (command == "genre_recommandation") {
            handle_genre_recommendation(args);
        } else {
            std::cerr << "Invalid command: " << command << std::endl;
        }
    }
}

void Recommender::handle_genre_recommendation(const std::vector<std::string>& args) {
    std::unique_ptr<IScoringStrategy> strategy;
    std::string genre;
    
    if (args.size() == 2) {
        const std::string& username = args[0];
        genre = args[1];
        
        auto it = user_lookup.find(username);
        if (it != user_lookup.end()) {
            const User* user = it->second;
            std::cout << "History scorer selected for user " << username << std::endl;
        } else {
            std::cout << "User '" << username << "' not found." << std::endl;
        }
    } else if (args.size() == 1) {
        genre = args[0];
        std::cout << "Generic scorer selected." << std::endl;
    } 
}


void Recommender::read_films(const std::string& file_path) {
    std::ifstream file(file_path);
    std::string line;
    std::getline(file, line); 

    while (std::getline(file, line)) {
        std::vector<std::string> tokens = split(line, CSV_DELIMITER);
        if (tokens.size() == 5) {
            films.emplace_back(tokens[0], tokens[1], tokens[2], tokens[3], std::stoi(tokens[4]));
        }
    }
}

void Recommender::read_users(const std::string& file_path) {
    std::map<std::string, const Film*> film_lookup;
    for (const auto& film : films) {
        film_lookup[film.get_name()] = &film;
    }

    std::ifstream file(file_path);
    std::string line;
    std::getline(file, line); 

    while (std::getline(file, line)) {
        std::vector<std::string> tokens = split(line, CSV_DELIMITER);
        if (tokens.size() != 3) continue;

        std::string username = tokens[0];
        std::vector<std::string> watched_names = split(tokens[1], LIST_DELIMITER);
        std::vector<std::string> ratings_str = split(tokens[2], LIST_DELIMITER);
        
        users.emplace_back(username);
        User& current_user = users.back();

        for (size_t i = 0; i < watched_names.size(); ++i) {
            auto it = film_lookup.find(watched_names[i]);
            if (it != film_lookup.end()) {
                const Film* film_ptr = it->second;
                Rating rating = string_to_rating(ratings_str[i]);
                current_user.add_watched_film(film_ptr, rating);
            }
        }
    }
}