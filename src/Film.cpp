#include "Film.h"

Film::Film(const std::string &name, const std::string &director, const std::string &cast, const std::string &genre, int imdb)
    : name(name), director(director), cast(cast), genre(genre), imdb(imdb) {}

Film::Film(const std::vector<std::string> &tokens)
{
    if (tokens.size() == 5)
    {
        name = tokens[0];
        director = tokens[1];
        cast = tokens[2];
        genre = tokens[3];
        imdb = std::stoi(tokens[4]);
    }
}

Film::Film() : imdb(0)
{
}
