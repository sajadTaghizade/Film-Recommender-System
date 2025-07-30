#ifndef RATING_H
#define RATING_H

#include "includes.h"

enum class Rating
{
    Perfect,
    Average,
    Poor
};

Rating string_to_rating(const std::string &str);

std::string rating_to_string(Rating r);

#endif