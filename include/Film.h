#ifndef FILM_H
#define FILM_H

#include "includes.h" 

class Film {
public:
    Film(const std::string& name, const std::string& director,const std::string& cast, const std::string& genre, int imdb);

    void print() const;

    std::string get_name() const { return name; }
    std::string get_genre() const { return genre; }
    int get_imdb() const { return imdb; }

private:
    std::string name;
    std::string director;
    std::string cast;
    std::string genre;
    int imdb;
};

#endif
