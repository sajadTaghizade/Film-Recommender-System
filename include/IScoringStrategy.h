#ifndef ISCORINGSTRATEGY_H
#define ISCORINGSTRATEGY_H

#include "includes.h"
#include "Film.h"

class IScoringStrategy {
public:
    virtual ~IScoringStrategy() = default;
    virtual std::vector<Film> get_recommendations(const std::vector<Film>& all_films, int count) const = 0;
};

#endif
