#ifndef HISTORYSCORER_H
#define HISTORYSCORER_H

#include "IScoringStrategy.h"
#include "User.h"
#include "GenericScorer.h"

class HistoryScorer : public IScoringStrategy {
public:
    HistoryScorer(const User* user);
    std::vector<Film> get_recommendations(const std::vector<Film>& genre_films, int count) const override;

private:
    std::vector<ScoredFilm> score_unwatched_films(const std::vector<Film>& films) const;
    
    std::pair<double, double> calculate_effects(const Film& film) const;

    static void sort_films(std::vector<ScoredFilm>& films);

    static std::vector<Film> extract_top_films(const std::vector<ScoredFilm>& films, int count);

    const User* current_user;
};

#endif
