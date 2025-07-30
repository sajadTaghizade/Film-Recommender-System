#include "HistoryScorer.h"
#include "includes.h"
#include "constants.h"

HistoryScorer::HistoryScorer(const User *user) : current_user(user) {}

std::vector<Film> HistoryScorer::get_recommendations(const std::vector<Film> &genre_films, int count) const
{
    std::vector<ScoredFilm> scored_films = score_unwatched_films(genre_films);
    sort_films(scored_films);
    return extract_top_films(scored_films, count);
}

std::vector<ScoredFilm> HistoryScorer::score_unwatched_films(const std::vector<Film> &films) const
{
    std::vector<ScoredFilm> scored_films;
    for (const auto &film : films)
    {
        if (current_user->has_watched(film))
        {
            continue;
        }

        auto [director_effect, cast_effect] = calculate_effects(film);

        double score = (film.get_imdb() * HISTORY_IMDB_WEIGHT) +
                       (director_effect * HISTORY_DIRECTOR_WEIGHT) +
                       (cast_effect * HISTORY_CAST_WEIGHT);

        scored_films.push_back({film, score});
    }
    return scored_films;
}

std::pair<double, double> HistoryScorer::calculate_effects(const Film &film) const
{
    double director_effect = DEFAULT_SCORE;
    double cast_effect = DEFAULT_SCORE;
    const auto &user_history = current_user->get_watched_history();

    for (const auto &[watched_film, rating] : user_history)
    {
        if (watched_film->get_genre() == film.get_genre())
        {
            if (watched_film->get_director() == film.get_director())
            {
                if (rating == Rating::Perfect)
                    director_effect = EFFECT_PERFECT;
                else if (rating == Rating::Average)
                    director_effect = EFFECT_AVERAGE;
                else if (rating == Rating::Poor)
                    director_effect = EFFECT_POOR;
            }
            if (watched_film->get_cast() == film.get_cast())
            {
                if (rating == Rating::Perfect)
                    cast_effect = EFFECT_PERFECT;
                else if (rating == Rating::Average)
                    cast_effect = EFFECT_AVERAGE;
                else if (rating == Rating::Poor)
                    cast_effect = EFFECT_POOR;
            }
        }
    }
    return {director_effect, cast_effect};
}

void HistoryScorer::sort_films(std::vector<ScoredFilm> &films)
{
    std::sort(films.begin(), films.end(), [](const ScoredFilm &a, const ScoredFilm &b)
              {
        if (a.score != b.score) return a.score > b.score;
        if (a.film.get_imdb() != b.film.get_imdb()) return a.film.get_imdb() > b.film.get_imdb();
        return a.film.get_name() < b.film.get_name(); });
}

std::vector<Film> HistoryScorer::extract_top_films(const std::vector<ScoredFilm> &films, int count)
{
    std::vector<Film> recommendations;
    for (int i = 0; i < std::min((int)films.size(), count); ++i)
    {
        recommendations.push_back(films[i].film);
    }
    return recommendations;
}