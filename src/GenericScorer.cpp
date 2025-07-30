#include "GenericScorer.h"
#include "includes.h"
#include "constants.h"

GenericScorer::GenericScorer(const std::map<std::string, FilmStats> &stats) : film_stats(stats) {}

std::vector<Film> GenericScorer::get_recommendations(const std::vector<Film> &genre_films, int count) const
{
    std::vector<ScoredFilm> scored_films = score_films(genre_films);

    sort_films(scored_films);

    return extract_top_films(scored_films, count);
}

std::vector<ScoredFilm> GenericScorer::score_films(const std::vector<Film> &films) const
{
    std::vector<ScoredFilm> scored_films;
    for (const auto &film : films)
    {
        double score = DEFAULT_SCORE;
        auto it = film_stats.find(film.get_name());

        if (it != film_stats.end())
        {
            const FilmStats &stats = it->second;
            score = (stats.perfect_ratings * GENERIC_PERFECT_WEIGHT) +
                    (stats.average_ratings * GENERIC_AVERAGE_WEIGHT) +
                    (stats.poor_ratings * GENERIC_POOR_WEIGHT);
        }

        scored_films.push_back({film, score});
    }
    return scored_films;
}

void GenericScorer::sort_films(std::vector<ScoredFilm> &films)
{
    std::sort(films.begin(), films.end(), [](const ScoredFilm &a, const ScoredFilm &b)
              {
        if (a.score != b.score) return a.score > b.score;
        if (a.film.get_imdb() != b.film.get_imdb()) return a.film.get_imdb() > b.film.get_imdb();
        return a.film.get_name() < b.film.get_name(); });
}

std::vector<Film> GenericScorer::extract_top_films(const std::vector<ScoredFilm> &films, int count)
{
    std::vector<Film> recommendations;
    for (int i = 0; i < std::min((int)films.size(), count); i++)
    {
        recommendations.push_back(films[i].film);
    }
    return recommendations;
}