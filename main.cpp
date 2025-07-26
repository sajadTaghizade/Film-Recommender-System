#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Film.h"

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

    if (std::getline(file, line)) {
    }

    while (std::getline(file, line)) {
        std::vector<std::string> tokens = split(line, ',');
        if (tokens.size() == 5) {
            std::string name = tokens[0];
            std::string director = tokens[1];
            std::string cast = tokens[2];
            std::string genre = tokens[3];
            int imdb = std::stoi(tokens[4]); 
            films.emplace_back(name, director, cast, genre, imdb);
        }
    }
    return films;
}


int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <users_file.csv> <films_file.csv>" << std::endl;
        return 1;
    }

    std::string users_filepath = argv[1];
    std::string films_filepath = argv[2];

    std::cout << " films: " << films_filepath << std::endl;

    std::vector<Film> all_films = read_films(films_filepath);

    std::cout << "---  Films  ---" << std::endl;
    for (const auto& film : all_films) {
        film.print();
    }
    std::cout << "-" << std::endl;

    return 0;
}