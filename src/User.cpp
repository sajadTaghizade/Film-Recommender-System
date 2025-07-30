#include "User.h"
#include "constants.h"
#include "utils.h" 

User::User(const std::vector<std::string> &tokens)
{
    if (!tokens.empty())
    {
        this->username = tokens[0];
    }
}

User::User(const std::string &username) : username(username) {}

void User::add_watched_film(const Film *film, Rating rating)
{
    watched_history[film] = rating;
}

std::string User::get_username() const
{
    return username;
}

bool User::has_watched(const Film &film) const
{
    for (const auto &pair : watched_history)
    {
        if (pair.first->get_name() == film.get_name())
        {
            return true;
        }
    }
    return false;
}

const std::map<const Film *, Rating> &User::get_watched_history() const
{
    return watched_history;
}

std::string User::get_favorite_genre() const
{
    if (watched_history.empty())
    {
        return "";
    }

    std::map<std::string, int> genre_counts;
    for (const auto &[film_ptr, rating] : watched_history)
    {
        genre_counts[film_ptr->get_genre()]++;
    }

    std::string favorite_genre = "";
    int max_count = 0;
    for (const auto &[genre, count] : genre_counts)
    {
        if (count > max_count)
        {
            max_count = count;
            favorite_genre = genre;
        }
    }
    return favorite_genre;
}

void User::link_watched_history(const std::vector<std::string> &tokens, const std::map<std::string, const Film *> &film_lookup)
{
    if (tokens.size() != 3)
        return;

    std::vector<std::string> watched_names = split(tokens[1], LIST_DELIMITER);
    std::vector<std::string> ratings_str = split(tokens[2], LIST_DELIMITER);

    for (size_t i = 0; i < watched_names.size(); ++i)
    {
        auto it = film_lookup.find(watched_names[i]);
        if (it != film_lookup.end())
        {
            const Film *film_ptr = it->second;
            Rating rating = string_to_rating(ratings_str[i]);
            add_watched_film(film_ptr, rating);
        }
    }
}