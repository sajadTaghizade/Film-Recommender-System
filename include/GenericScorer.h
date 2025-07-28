#ifndef GENERICSCORER_H
#define GENERICSCORER_H

#include "IScoringStrategy.h"
#include "User.h"

struct ScoredFilm {
    Film film;
    double score;
};

class GenericScorer : public IScoringStrategy {
public:
    GenericScorer(const std::map<std::string, FilmStats>& stats);
    std::vector<Film> get_recommendations(const std::vector<Film>& genre_films, int count) const override;

private:
    std::vector<ScoredFilm> score_films(const std::vector<Film>& films) const;
    
    static void sort_films(std::vector<ScoredFilm>& films);

    static std::vector<Film> extract_top_films(const std::vector<ScoredFilm>& films, int count);

    const std::map<std::string, FilmStats>& film_stats;
};

#endif 
