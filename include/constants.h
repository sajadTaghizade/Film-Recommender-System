#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "includes.h"

const char CSV_DELIMITER = ',';
const char LIST_DELIMITER = ';';
const char DOUBLE_QUOTE = '"';

const std::string EXIT_CMD = "exit";
const std::string QUIT_CMD = "quit";
const std::string GENRE_CMD = "genre_recommandation";
const std::string CAST_CMD = "cast_recommandation";

const std::string PERFECT = "Perfect";
const std::string AVERAGE = "Average";
const std::string POOR = "Poor";
const std::string NO_RATING = "";

const std::string USER_NOT_FOUND_MSG_P1 = "Error: User '";
const std::string USER_NOT_FOUND_MSG_P2 = "' not found.";
const std::string INVALID_ARGS_GENRE_MSG = "Error: Invalid arguments for genre_recommandation";
const std::string INVALID_ARGS_CAST_MSG = "Error: Invalid arguments for cast_recommandation";
const std::string NO_FILMS_FOR_GENRE_MSG = "No films found for genre: ";
const std::string NO_SUITABLE_FILMS_MSG = "No suitable movies were found.";
const std::string INVALID_CMD_MSG = "Invalid command: ";

const std::string RANK_SEPARATOR = ". ";
const std::string NAME_SEPARATOR = ": ";
const std::string IMDB_PREFIX = " (";
const std::string IMDB_SUFFIX = ")";

const int ARGS_WITH_USER = 2;
const int ARGS_NO_USER = 1;
const int GENRE_REC_COUNT = 3;
const int CAST_REC_COUNT = 2;
const int FILM_FILE_COLS = 5;
const int USER_FILE_COLS = 3;

const double DEFAULT_SCORE = 0.0;

const double GENERIC_PERFECT_WEIGHT = 0.7;
const double GENERIC_AVERAGE_WEIGHT = 0.5;
const double GENERIC_POOR_WEIGHT = -0.2;

const double HISTORY_IMDB_WEIGHT = 0.7;
const double HISTORY_DIRECTOR_WEIGHT = 0.5;
const double HISTORY_CAST_WEIGHT = 0.6;

const int EFFECT_PERFECT = 10;
const int EFFECT_AVERAGE = 5;
const int EFFECT_POOR = -1;


#endif 