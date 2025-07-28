#ifndef RECOMMENDER_H
#define RECOMMENDER_H

#include "includes.h"
#include "Film.h"
#include "User.h"
#include "IScoringStrategy.h"
#include "includes.h"


class Recommender {
public:
    void run(const std::string& users_path, const std::string& films_path);

private:
    void load_data(const std::string& films_path, const std::string& users_path);
    void read_films(const std::string& file_path);
    void read_users(const std::string& file_path);
    
    void process_commands();
    std::vector<std::string> parse_arguments(std::stringstream& ss);

    void handle_genre_recommendation(const std::vector<std::string>& args);
    std::unique_ptr<IScoringStrategy> select_genre_strategy(const std::vector<std::string>& args, std::string& out_genre);
    std::vector<Film> filter_films_by_genre(const std::string& genre) const;

    void handle_cast_recommendation(const std::vector<std::string>& args);
    void recommend_cast_with_history(const std::string& username, const std::string& cast_name);
    void recommend_cast_no_history(const std::string& cast_name);
    void sort_and_print_cast_recs(std::vector<Film>& films);

    void print_recommendations(const std::vector<Film>& recommendations, int count);

    std::vector<Film> films;
    std::vector<User> users;
    std::map<std::string, const User*> user_lookup;
    std::map<std::string, FilmStats> film_stats_cache;
};

#endif