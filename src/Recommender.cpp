#include "Recommender.h"
#include "utils.h"
#include "constants.h"
#include "Rating.h"
#include "GenericScorer.h"
#include "HistoryScorer.h"
#include "DataLoader.h"

void Recommender::run(const std::string &users_path, const std::string &films_path)
{
    load_data(films_path, users_path);
    process_commands();
}

void Recommender::process_commands()
{
    std::string line;
    while (std::getline(std::cin, line))
    {
        if (line.empty())
            continue;

        std::stringstream ss(line);
        std::string command;
        ss >> command;

        if (command == EXIT_CMD || command == QUIT_CMD)
        {
            break;
        }

        std::vector<std::string> args = parse_arguments(ss);

        if (command == GENRE_CMD)
        {
            handle_genre_recommendation(args);
        }
        else if (command == CAST_CMD)
        {
            handle_cast_recommendation(args);
        }
        else
        {
            std::cerr << INVALID_CMD_MSG << command << std::endl;
        }
    }
}

std::vector<std::string> Recommender::parse_arguments(std::stringstream &ss)
{
    std::vector<std::string> args;
    std::string current_arg;
    while (ss >> std::ws && !ss.eof())
    {
        if (ss.peek() == DOUBLE_QUOTE)
        {
            ss.get();
            if (std::getline(ss, current_arg, DOUBLE_QUOTE))
            {
                args.push_back(current_arg);
            }
        }
        else
        {
            if (ss >> current_arg)
            {
                args.push_back(current_arg);
            }
        }
    }
    return args;
}

void Recommender::handle_genre_recommendation(const std::vector<std::string> &args)
{
    std::string genre;
    std::unique_ptr<IScoringStrategy> strategy = select_genre_strategy(args, genre);

    if (!strategy)
    {
        return;
    }

    std::vector<Film> genre_films = filter_films_by_genre(genre);

    if (genre_films.empty())
    {
        std::cout << NO_FILMS_FOR_GENRE_MSG << genre << std::endl;
        return;
    }

    std::vector<Film> recommendations = strategy->get_recommendations(genre_films, GENRE_REC_COUNT);
    print_recommendations(recommendations, GENRE_REC_COUNT);
}

std::unique_ptr<IScoringStrategy> Recommender::select_genre_strategy(const std::vector<std::string> &args, std::string &out_genre)
{
    if (args.size() == ARGS_WITH_USER)
    {
        const std::string &username = args[0];
        out_genre = args[1];

        auto it = user_lookup.find(username);
        if (it != user_lookup.end())
        {
            return std::make_unique<HistoryScorer>(it->second);
        }
        else
        {
            std::cerr << USER_NOT_FOUND_MSG_P1 << username << USER_NOT_FOUND_MSG_P2 << std::endl;
            return nullptr;
        }
    }
    else if (args.size() == ARGS_NO_USER)
    {
        out_genre = args[0];
        return std::make_unique<GenericScorer>(film_stats_cache);
    }
    else
    {
        std::cerr << INVALID_ARGS_GENRE_MSG << std::endl;
        return nullptr;
    }
}

std::vector<Film> Recommender::filter_films_by_genre(const std::string &genre) const
{
    std::vector<Film> genre_films;
    for (const auto &film : films)
    {
        if (film.get_genre() == genre)
        {
            genre_films.push_back(film);
        }
    }
    return genre_films;
}

void Recommender::handle_cast_recommendation(const std::vector<std::string> &args)
{
    if (args.size() == ARGS_WITH_USER)
    {
        recommend_cast_with_history(args[0], args[1]);
    }
    else if (args.size() == ARGS_NO_USER)
    {
        recommend_cast_no_history(args[0]);
    }
    else
    {
        std::cerr << INVALID_ARGS_CAST_MSG << std::endl;
    }
}

void Recommender::recommend_cast_with_history(const std::string &username, const std::string &cast_name)
{
    auto it = user_lookup.find(username);
    if (it == user_lookup.end())
    {
        std::cerr << USER_NOT_FOUND_MSG_P1 << username << USER_NOT_FOUND_MSG_P2 << std::endl;
        return;
    }
    const User *user = it->second;
    std::string favorite_genre = user->get_favorite_genre();
    std::vector<Film> recommendations;
    for (const auto &film : films)
    {
        if (film.get_cast() == cast_name && film.get_genre() == favorite_genre && !user->has_watched(film))
        {
            recommendations.push_back(film);
        }
    }
    sort_and_print_cast_recs(recommendations);
}

void Recommender::recommend_cast_no_history(const std::string &cast_name)
{
    std::vector<Film> recommendations;
    for (const auto &film : films)
    {
        if (film.get_cast() == cast_name)
        {
            recommendations.push_back(film);
        }
    }
    sort_and_print_cast_recs(recommendations);
}

void Recommender::sort_and_print_cast_recs(std::vector<Film> &films)
{
    std::sort(films.begin(), films.end(), [](const Film &a, const Film &b)
              {
        if (a.get_imdb() != b.get_imdb()) return a.get_imdb() > b.get_imdb();
        return a.get_name() < b.get_name(); });
    print_recommendations(films, CAST_REC_COUNT);
}

void Recommender::print_recommendations(const std::vector<Film> &recommendations, int count)
{
    if (recommendations.empty())
    {
        std::cout << NO_SUITABLE_FILMS_MSG << std::endl;
    }
    else
    {
        int rank = 1;
        for (int i = 0; i < std::min((int)recommendations.size(), count); i++)
        {
            const auto &film = recommendations[i];
            std::cout << rank++ << RANK_SEPARATOR << film.get_name() << NAME_SEPARATOR
                      << film.get_director() << IMDB_PREFIX << film.get_imdb() << IMDB_SUFFIX << std::endl;
        }
    }
}

void Recommender::load_data(const std::string &films_path, const std::string &users_path)
{
    this->films = DataLoader<Film>::load_from_csv(films_path);

    std::map<std::string, const Film *> film_lookup;
    for (const auto &film : this->films)
    {
        film_lookup[film.get_name()] = &film;
    }

    std::ifstream users_file(users_path);
    std::string line;
    std::getline(users_file, line);

    while (std::getline(users_file, line))
    {
        std::vector<std::string> tokens = split(line, CSV_DELIMITER);
        if (tokens.size() != 3)
            continue;

        this->users.emplace_back(tokens);

        this->users.back().link_watched_history(tokens, film_lookup);
    }

    for (const auto &user : this->users)
    {
        for (const auto &[film_ptr, rating] : user.get_watched_history())
        {
            if (rating == Rating::Perfect)
                film_stats_cache[film_ptr->get_name()].perfect_ratings++;
            else if (rating == Rating::Average)
                film_stats_cache[film_ptr->get_name()].average_ratings++;
            else if (rating == Rating::Poor)
                film_stats_cache[film_ptr->get_name()].poor_ratings++;
        }
    }

    for (const auto &user : this->users)
    {
        user_lookup[user.get_username()] = &user;
    }
}

void Recommender::read_films(const std::string &file_path)
{
    std::ifstream file(file_path);
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line))
    {
        std::vector<std::string> tokens = split(line, CSV_DELIMITER);
        if (tokens.size() == FILM_FILE_COLS)
        {
            films.emplace_back(tokens[0], tokens[1], tokens[2], tokens[3], std::stoi(tokens[4]));
        }
    }
}

void Recommender::read_users(const std::string &file_path)
{
    std::map<std::string, const Film *> film_lookup;
    for (const auto &film : films)
    {
        film_lookup[film.get_name()] = &film;
    }
    std::ifstream file(file_path);
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line))
    {
        std::vector<std::string> tokens = split(line, CSV_DELIMITER);
        if (tokens.size() != USER_FILE_COLS)
            continue;
        std::string username = tokens[0];
        std::vector<std::string> watched_names = split(tokens[1], LIST_DELIMITER);
        std::vector<std::string> ratings_str = split(tokens[2], LIST_DELIMITER);
        users.emplace_back(username);
        User &current_user = users.back();
        for (size_t i = 0; i < watched_names.size(); i++)
        {
            auto it = film_lookup.find(watched_names[i]);
            if (it != film_lookup.end())
            {
                const Film *film_ptr = it->second;
                Rating rating = string_to_rating(ratings_str[i]);
                current_user.add_watched_film(film_ptr, rating);
            }
        }
    }
}

bool Recommender::user_exists(const std::string &username) const
{
    return user_lookup.count(username);
}

std::vector<std::string> Recommender::get_all_genres() const
{
    std::set<std::string> genres;
    for (const auto &film : films)
    {
        genres.insert(film.get_genre());
    }
    return std::vector<std::string>(genres.begin(), genres.end());
}

std::vector<Film> Recommender::get_recommendations_for_genre(const std::string &username, const std::string &genre)
{
    std::unique_ptr<IScoringStrategy> strategy;
    if (!username.empty() && user_exists(username))
    {
        strategy = std::make_unique<HistoryScorer>(user_lookup.at(username));
    }
    else
    {
        strategy = std::make_unique<GenericScorer>(film_stats_cache);
    }

    std::vector<Film> genre_films = filter_films_by_genre(genre);
    if (genre_films.empty())
    {
        return {};
    }
    return strategy->get_recommendations(genre_films, GENRE_REC_COUNT);
}

std::vector<Film> Recommender::get_recommendations_for_cast(const std::string &username, const std::string &cast_name)
{
    std::vector<Film> recommendations;

    if (!username.empty() && user_exists(username))
    {
        const User *user = user_lookup.at(username);
        std::string favorite_genre = user->get_favorite_genre();
        for (const auto &film : films)
        {
            if (film.get_cast() == cast_name && film.get_genre() == favorite_genre && !user->has_watched(film))
            {
                recommendations.push_back(film);
            }
        }
    }
    else
    {
        for (const auto &film : films)
        {
            if (film.get_cast() == cast_name)
            {
                recommendations.push_back(film);
            }
        }
    }

    std::sort(recommendations.begin(), recommendations.end(), [](const Film &a, const Film &b)
              {
        if (a.get_imdb() != b.get_imdb()) return a.get_imdb() > b.get_imdb();
        return a.get_name() < b.get_name(); });

    if (recommendations.size() > CAST_REC_COUNT)
    {
        recommendations.resize(CAST_REC_COUNT);
    }

    return recommendations;
}

std::vector<std::string> Recommender::get_all_casts() const
{
    std::set<std::string> casts;
    for (const auto &film : films)
    {
        casts.insert(film.get_cast());
    }
    return std::vector<std::string>(casts.begin(), casts.end());
}

const std::vector<Film> &Recommender::get_all_films() const
{
    return films;
}
FilmDetails Recommender::get_film_details(const std::string &film_name) const
{
    FilmDetails details;
    std::string path_name = film_name;
    std::transform(path_name.begin(), path_name.end(), path_name.begin(), ::tolower);
    std::replace(path_name.begin(), path_name.end(), ' ', '_');

    std::ifstream file(DESCRIPTIONS_PATH + path_name + DESCRIPTION_EXT);
    if (!file)
    {
        details.plot_summary = NO_DESCRIPTION_MSG;
        return details;
    }

    std::string line;
    bool plot_section = false;
    std::stringstream plot_stream;

    while (std::getline(file, line))
    {
        if (line.find(PLOT_SECTION_TAG) != std::string::npos)
        {
            plot_section = true;
            continue;
        }

        if (plot_section)
        {
            plot_stream << line << "\n";
        }
        else
        {
            size_t separator_pos = line.find(KEY_SEPARATOR);
            if (separator_pos != std::string::npos)
            {
                std::string key = line.substr(0, separator_pos);
                std::string value = line.substr(separator_pos + KEY_SEPARATOR.length());

                if (key == KEY_DIRECTOR)
                    details.director = value;
                else if (key == KEY_WRITERS)
                    details.writers = value;
                else if (key == KEY_COMPOSER)
                    details.composer = value;
                else if (key == KEY_CINEMATOGRAPHER)
                    details.cinematographer = value;
                else if (key == KEY_PROD_COMPANIES)
                    details.production_companies = value;
                else if (key == KEY_MAIN_CAST)
                {
                    std::stringstream cast_ss(value);
                    std::string cast_member;
                    while (std::getline(cast_ss, cast_member, CAST_DELIMITER))
                    {
                        cast_member.erase(0, cast_member.find_first_not_of(" \t\n\r"));
                        cast_member.erase(cast_member.find_last_not_of(" \t\n\r") + 1);
                        details.main_cast.push_back(cast_member);
                    }
                }
            }
        }
    }
    details.plot_summary = plot_stream.str();
    return details;
}