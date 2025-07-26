#include "includes.h"
#include "constants.h"
#include "Film.h"
#include "User.h"
#include "Rating.h"

std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

std::vector<Film> read_films(const std::string& file_path) {
    std::vector<Film> films;
    std::ifstream file(file_path);
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        std::vector<std::string> tokens = split(line, CSV_DELIMITER);
        if (tokens.size() == 5) {
            films.emplace_back(tokens[0], tokens[1], tokens[2], tokens[3], std::stoi(tokens[4]));
        }
    }
    return films;
}

std::vector<User> read_users(const std::string& file_path, const std::vector<Film>& all_films) {
    std::vector<User> users;
    
    std::map<std::string, const Film*> film_lookup;
    for (const auto& film : all_films) {
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
            const Film* film_ptr = film_lookup.at(watched_names[i]);
            Rating rating = string_to_rating(ratings_str[i]);
            current_user.add_watched_film(film_ptr, rating);
        }
    }
    return users;
}


int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <users_file.csv> <films_file.csv>" << std::endl;
        return 1;
    }

    std::string users_filepath = argv[1];
    std::string films_filepath = argv[2];

    std::vector<Film> all_films = read_films(films_filepath);

    std::vector<User> all_users = read_users(users_filepath, all_films);
    
    std::cout << "---  Users  ---" << std::endl;
    for (const auto& user : all_users) {
        user.print();
        std::cout << std::endl;
    }
    std::cout << "------------------------" << std::endl;

    return 0;
}