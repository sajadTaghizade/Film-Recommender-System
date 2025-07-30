#ifndef CONSTANTS2_H
#define CONSTANTS2_H

#include "includes.h"


const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 800;
const unsigned int FRAMERATE_LIMIT = 60;
const std::string APP_TITLE = "What to Watch?";

const std::string FONT_PATH = "font/arial.ttf";
const std::string BACKGROUND_PATH = "images/background/background.jpeg";
const std::string GENRES_IMG_PATH = "images/genres/";
const std::string ACTORS_IMG_PATH = "images/actors/";
const std::string POSTERS_IMG_PATH = "images/posters/";
const std::string DESC_PATH = "descriptions/";

const sf::Color BG_COLOR = sf::Color(40, 42, 54);
const sf::Color TEXT_COLOR = sf::Color(248, 248, 242);
const sf::Color ACCENT_COLOR = sf::Color(139, 233, 253);
const sf::Color HOVER_COLOR = sf::Color::Yellow;
const sf::Color INPUT_BOX_BG_COLOR = sf::Color(0, 0, 0, 120);

const unsigned int FONT_SIZE_LARGE_TITLE = 50;
const unsigned int FONT_SIZE_TITLE = 40;
const unsigned int FONT_SIZE_HEADER = 32;
const unsigned int FONT_SIZE_SUBHEADER = 28;
const unsigned int FONT_SIZE_BODY = 22;
const unsigned int FONT_SIZE_SMALL = 18;
const unsigned int FONT_SIZE_TINY = 14;

const sf::Vector2f INPUT_BOX_SIZE(300.f, 40.f);
const sf::Vector2f CARET_SIZE(2.f, 28.f);

const int GENRES_PER_ROW = 3;
const sf::Vector2f GENRE_TARGET_SIZE(200.f, 120.f);
const float G_START_X = 60.f, G_START_Y = 120.f;
const float G_PADDING_X = 60.f, G_PADDING_Y = 80.f;

const int CASTS_PER_ROW = 5;
const sf::Vector2f CAST_TARGET_SIZE(120.f, 160.f);
const float C_START_X = 40.f, C_START_Y = 120.f;
const float C_PADDING_X = 30.f, C_PADDING_Y = 60.f;

const int RESULTS_PER_ROW = 3;
const sf::Vector2f RESULT_TARGET_SIZE(200.f, 280.f);
const float R_START_X = 60.f, R_START_Y = 120.f;
const float R_PADDING_X = 60.f, R_PADDING_Y = 100.f;

const float DETAILS_POSTER_X = 50.f;
const float DETAILS_POSTER_Y = 120.f;
const float DETAILS_POSTER_WIDTH = 300.f;
const float DETAILS_TEXT_X = 380.f;
const float DETAILS_TEXT_Y = 120.f;
const unsigned int DETAILS_WRAP_CHARS = 40;

const float BACK_PROMPT_Y = 750.f;

const std::string LOGIN_PROMPT = "Enter Username";
const std::string MENU_TITLE = "Main Menu";
const std::string GENRE_BUTTON_TEXT = "Recommend by Genre";
const std::string CAST_BUTTON_TEXT = "Recommend by Cast";
const std::string GENRE_SELECT_TITLE = "Select a Genre";
const std::string CAST_SELECT_TITLE = "Select an Actor";
const std::string RESULTS_TITLE = "Recommendations";
const std::string RESULTS_PROMPT = "Click on a poster for details";
const std::string NO_RESULTS_MSG = "No suitable movies were found.";
const std::string BACK_TO_MENU_MSG = "(Press ESC to return to main menu)";
const std::string BACK_TO_RESULTS_MSG = "(Press ESC to return to results)";

#endif 
