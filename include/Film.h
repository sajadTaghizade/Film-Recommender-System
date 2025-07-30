#ifndef FILM_H
#define FILM_H

#include "includes.h"

struct FilmStats
{
    int perfect_ratings = 0;
    int average_ratings = 0;
    int poor_ratings = 0;
};

struct FilmDetails
{
    std::string director;
    std::string writers;
    std::string composer;
    std::string cinematographer;
    std::string production_companies;
    std::vector<std::string> main_cast;
    std::string plot_summary;
};

class Film
{
public:
    Film(const std::string &name, const std::string &director,
         const std::string &cast, const std::string &genre, int imdb);

    explicit Film(const std::vector<std::string> &tokens);
    Film();

    std::string get_name() const { return name; }
    std::string get_genre() const { return genre; }
    std::string get_director() const { return director; }
    std::string get_cast() const { return cast; }
    int get_imdb() const { return imdb; }

private:
    std::string name;
    std::string director;
    std::string cast;
    std::string genre;
    int imdb;
};

#endif
