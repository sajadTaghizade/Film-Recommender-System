#include <SFML/Graphics.hpp>
#include "Recommender.h"
#include "includes.h"
#include "constants2.h"
#include <set>

enum class AppState { Login, MainMenu, GenreSelect, CastSelect, ShowResults, MovieDetails };

struct ImageButton {
    sf::Sprite sprite;
    sf::Text text;
    std::string name;
};

struct UIComponents {
    sf::Sprite background_sprite;
    sf::Texture background_texture;
    sf::Text main_title, prompt_text, text_input_field, menu_title, genre_button, cast_button,
             genre_title, cast_title, results_title, back_prompt, description_text;
    sf::RectangleShape input_box;
    sf::RectangleShape caret; 
    std::vector<ImageButton> genre_buttons;
    std::vector<ImageButton> cast_buttons;
    std::vector<ImageButton> results_buttons;
};

struct AppContext {
    sf::RenderWindow& window;
    sf::Font& font;
    Recommender& app_logic;
    AppState currentState = AppState::Login;
    std::string current_user = "";
    std::string input_text = "";
    std::vector<Film> current_recommendations;
    const Film* selected_film = nullptr;
    UIComponents ui;
    std::map<std::string, sf::Texture> texture_cache;
    sf::Clock caret_clock; 
};

void create_ui_components(AppContext& context);
void process_events(AppContext& context);
void update(AppContext& context);
void render(AppContext& context);
void setup_image_paths(Recommender& recommender_app, std::map<std::string, std::string>& image_paths);
void load_textures(const std::map<std::string, std::string>& image_paths, std::map<std::string, sf::Texture>& texture_cache);
void handle_text_input(AppContext& context, sf::Event& event);
void render_login(AppContext& context);
void render_main_menu(AppContext& context);
void render_selection_screen(AppContext& context, const sf::Text& title, const std::vector<ImageButton>& buttons);
void render_results(AppContext& context);
void render_movie_details(AppContext& context);
std::string wrap_text(const std::string& text, unsigned int line_width_chars);
void center_text(sf::Text& text);

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <path/to/users.csv> <path/to/films.csv>" << std::endl;
        return 1;
    }

    Recommender recommender_app;
    recommender_app.load_data(argv[2], argv[1]);
    
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), APP_TITLE);
    window.setFramerateLimit(FRAMERATE_LIMIT);
    
    sf::Font font;
    if (!font.loadFromFile(FONT_PATH)) {
        std::cerr << "Error: Could not load font '" << FONT_PATH << "'" << std::endl;
        return -1;
    }

    AppContext context = {window, font, recommender_app};
    create_ui_components(context);

    while (window.isOpen()) {
        process_events(context);
        update(context);
        render(context);
    }

    return 0;
}

void setup_image_paths(Recommender& recommender_app, std::map<std::string, std::string>& image_paths) {
    auto create_path = [](const std::string& name) {
        std::string path = name;
        std::transform(path.begin(), path.end(), path.begin(), ::tolower);
        std::replace(path.begin(), path.end(), ' ', '_');
        return path;
    };
    for (const auto& genre : recommender_app.get_all_genres()) {
        image_paths[genre] = GENRES_IMG_PATH + create_path(genre) + ".jpeg";
    }
    for (const auto& cast : recommender_app.get_all_casts()) {
        image_paths[cast] = ACTORS_IMG_PATH + create_path(cast) + ".jpeg";
    }
    for (const auto& film : recommender_app.get_all_films()) {
        image_paths[film.get_name()] = POSTERS_IMG_PATH + create_path(film.get_name()) + ".jpeg";
    }
}

void load_textures(const std::map<std::string, std::string>& image_paths, std::map<std::string, sf::Texture>& texture_cache) {
    for (const auto& pair : image_paths) {
        sf::Texture texture;
        if (texture.loadFromFile(pair.second)) {
            texture_cache[pair.first] = texture;
        }
    }
}

void center_text(sf::Text& text) {
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
}

void create_ui_components(AppContext& context) {
    std::map<std::string, std::string> image_paths;
    setup_image_paths(context.app_logic, image_paths);
    load_textures(image_paths, context.texture_cache);

    if (context.ui.background_texture.loadFromFile(BACKGROUND_PATH)) {
        context.ui.background_sprite.setTexture(context.ui.background_texture);
        context.ui.background_sprite.setScale(
            (float)WINDOW_WIDTH / context.ui.background_texture.getSize().x,
            (float)WINDOW_HEIGHT / context.ui.background_texture.getSize().y
        );
        context.ui.background_sprite.setColor(sf::Color(255, 255, 255, 100));
    }

    context.ui.main_title = sf::Text(APP_TITLE, context.font, FONT_SIZE_LARGE_TITLE);
    context.ui.main_title.setFillColor(ACCENT_COLOR);
    center_text(context.ui.main_title);

    context.ui.prompt_text = sf::Text(LOGIN_PROMPT, context.font, FONT_SIZE_BODY);
    context.ui.prompt_text.setFillColor(TEXT_COLOR);
    center_text(context.ui.prompt_text);

    context.ui.input_box.setSize(INPUT_BOX_SIZE);
    context.ui.input_box.setOrigin(INPUT_BOX_SIZE.x / 2.f, INPUT_BOX_SIZE.y / 2.f);
    context.ui.input_box.setOutlineColor(ACCENT_COLOR);
    context.ui.input_box.setOutlineThickness(2);
    context.ui.input_box.setFillColor(INPUT_BOX_BG_COLOR);

    context.ui.text_input_field.setFont(context.font);
    context.ui.text_input_field.setCharacterSize(FONT_SIZE_BODY);
    context.ui.text_input_field.setFillColor(TEXT_COLOR);

    context.ui.caret.setSize(CARET_SIZE);
    context.ui.caret.setFillColor(ACCENT_COLOR);

    context.ui.menu_title = sf::Text(MENU_TITLE, context.font, FONT_SIZE_TITLE);
    context.ui.menu_title.setFillColor(ACCENT_COLOR);
    center_text(context.ui.menu_title);
    
    context.ui.genre_button = sf::Text(GENRE_BUTTON_TEXT, context.font, FONT_SIZE_SUBHEADER);
    context.ui.genre_button.setFillColor(TEXT_COLOR);
    center_text(context.ui.genre_button);

    context.ui.cast_button = sf::Text(CAST_BUTTON_TEXT, context.font, FONT_SIZE_SUBHEADER);
    context.ui.cast_button.setFillColor(TEXT_COLOR);
    center_text(context.ui.cast_button);

    context.ui.genre_title = sf::Text(GENRE_SELECT_TITLE, context.font, FONT_SIZE_HEADER);
    context.ui.genre_title.setFillColor(ACCENT_COLOR);
    center_text(context.ui.genre_title);

    auto genres = context.app_logic.get_all_genres();
    for (size_t i = 0; i < genres.size(); i++) {
        ImageButton button;
        button.name = genres[i];
        auto it = context.texture_cache.find(genres[i]);
        if (it != context.texture_cache.end()) {
            button.sprite.setTexture(it->second);
            sf::Vector2f o_size = sf::Vector2f(it->second.getSize());
            button.sprite.setScale(GENRE_TARGET_SIZE.x / o_size.x, GENRE_TARGET_SIZE.y / o_size.y);
        }
        int row = i / GENRES_PER_ROW;
        int col = i % GENRES_PER_ROW;
        float px = G_START_X + col * (GENRE_TARGET_SIZE.x + G_PADDING_X);
        float py = G_START_Y + row * (GENRE_TARGET_SIZE.y + G_PADDING_Y);
        button.sprite.setPosition(px, py);
        button.text = sf::Text(genres[i], context.font, FONT_SIZE_SMALL);
        button.text.setFillColor(TEXT_COLOR);
        button.text.setPosition(px + (GENRE_TARGET_SIZE.x - button.text.getGlobalBounds().width) / 2.f, py + GENRE_TARGET_SIZE.y + 10);
        context.ui.genre_buttons.push_back(button);
    }

    context.ui.cast_title = sf::Text(CAST_SELECT_TITLE, context.font, FONT_SIZE_HEADER);
    context.ui.cast_title.setFillColor(ACCENT_COLOR);
    center_text(context.ui.cast_title);

    auto casts = context.app_logic.get_all_casts();
    for (size_t i = 0; i < casts.size(); i++) {
        ImageButton actor_button;
        actor_button.name = casts[i];
        auto it = context.texture_cache.find(casts[i]);
        if (it != context.texture_cache.end()) {
            actor_button.sprite.setTexture(it->second);
            sf::Vector2f o_size = sf::Vector2f(it->second.getSize());
            actor_button.sprite.setScale(CAST_TARGET_SIZE.x / o_size.x, CAST_TARGET_SIZE.y / o_size.y);
        }
        int row = i / CASTS_PER_ROW;
        int col = i % CASTS_PER_ROW;
        float px = C_START_X + col * (CAST_TARGET_SIZE.x + C_PADDING_X);
        float py = C_START_Y + row * (CAST_TARGET_SIZE.y + C_PADDING_Y);
        actor_button.sprite.setPosition(px, py);
        actor_button.text = sf::Text(casts[i], context.font, FONT_SIZE_TINY);
        actor_button.text.setFillColor(TEXT_COLOR);
        actor_button.text.setPosition(px + (CAST_TARGET_SIZE.x - actor_button.text.getGlobalBounds().width) / 2.f, py + CAST_TARGET_SIZE.y + 5);
        context.ui.cast_buttons.push_back(actor_button);
    }

    context.ui.results_title = sf::Text(RESULTS_TITLE, context.font, FONT_SIZE_HEADER);
    context.ui.results_title.setFillColor(ACCENT_COLOR);
    center_text(context.ui.results_title);

    context.ui.back_prompt = sf::Text("", context.font, FONT_SIZE_SMALL);
    context.ui.back_prompt.setFillColor(TEXT_COLOR);
    center_text(context.ui.back_prompt);
}

void handle_text_input(AppContext& context, sf::Event& event) {
    if (event.text.unicode == '\b' && !context.input_text.empty()) {
        context.input_text.pop_back();
    } else if (event.text.unicode < 128 && event.text.unicode != '\b' && event.text.unicode != '\r' && event.text.unicode != '\n') {
        context.input_text += static_cast<char>(event.text.unicode);
    }
    context.ui.text_input_field.setString(context.input_text);
}

void process_events(AppContext& context) {
    sf::Event event;
    while (context.window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            context.window.close();
        }

        switch (context.currentState) {
            case AppState::Login:
                if (event.type == sf::Event::TextEntered) handle_text_input(context, event);
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                    context.current_user = context.input_text;
                    context.input_text.clear();
                    context.ui.text_input_field.setString("");
                    context.currentState = AppState::MainMenu;
                }
                break;
            case AppState::MainMenu:
                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2f m_pos = context.window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                    if (context.ui.genre_button.getGlobalBounds().contains(m_pos)) context.currentState = AppState::GenreSelect;
                    if (context.ui.cast_button.getGlobalBounds().contains(m_pos)) context.currentState = AppState::CastSelect;
                }
                break;
            case AppState::GenreSelect:
                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2f m_pos = context.window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                    for (const auto& btn : context.ui.genre_buttons) {
                        if (btn.sprite.getGlobalBounds().contains(m_pos)) {
                            context.current_recommendations = context.app_logic.get_recommendations_for_genre(context.current_user, btn.name);
                            context.currentState = AppState::ShowResults;
                            break;
                        }
                    }
                }
                break;
            case AppState::CastSelect:
                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2f m_pos = context.window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                    for (const auto& btn : context.ui.cast_buttons) {
                        if (btn.sprite.getGlobalBounds().contains(m_pos)) {
                            context.current_recommendations = context.app_logic.get_recommendations_for_cast(context.current_user, btn.name);
                            context.currentState = AppState::ShowResults;
                            break;
                        }
                    }
                }
                break;
            case AppState::ShowResults:
                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2f m_pos = context.window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                    for (const auto& btn : context.ui.results_buttons) {
                        if (btn.sprite.getGlobalBounds().contains(m_pos)) {
                            for(const auto& film : context.app_logic.get_all_films()) {
                                if (film.get_name() == btn.name) {
                                    context.selected_film = &film;
                                    break;
                                }
                            }
                            context.currentState = AppState::MovieDetails;
                            break;
                        }
                    }
                }
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    context.currentState = AppState::MainMenu;
                }
                break;
            case AppState::MovieDetails:
                if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Enter)) {
                    context.currentState = AppState::ShowResults;
                }
                break;
        }
    }
}

void update(AppContext& context) {
    if (context.currentState == AppState::Login) {
        float elapsed_time = context.caret_clock.getElapsedTime().asSeconds();
        if (elapsed_time > 1.0f) context.caret_clock.restart();
        sf::Color caret_color = (elapsed_time < 0.5f) ? ACCENT_COLOR : sf::Color::Transparent;
        context.ui.caret.setFillColor(caret_color);
        sf::Vector2f text_pos = context.ui.text_input_field.findCharacterPos(context.input_text.length());
        context.ui.caret.setPosition(text_pos);
    }
    
    sf::Vector2f mouse_pos = context.window.mapPixelToCoords(sf::Mouse::getPosition(context.window));
    if (context.currentState == AppState::MainMenu) {
        context.ui.genre_button.setFillColor(context.ui.genre_button.getGlobalBounds().contains(mouse_pos) ? HOVER_COLOR : TEXT_COLOR);
        context.ui.cast_button.setFillColor(context.ui.cast_button.getGlobalBounds().contains(mouse_pos) ? HOVER_COLOR : TEXT_COLOR);
    } else if (context.currentState == AppState::GenreSelect) {
        for (auto& button : context.ui.genre_buttons) {
            button.text.setFillColor(button.sprite.getGlobalBounds().contains(mouse_pos) ? HOVER_COLOR : TEXT_COLOR);
        }
    } else if (context.currentState == AppState::CastSelect) {
        for (auto& button : context.ui.cast_buttons) {
            button.text.setFillColor(button.sprite.getGlobalBounds().contains(mouse_pos) ? HOVER_COLOR : TEXT_COLOR);
        }
    } else if (context.currentState == AppState::ShowResults) {
        context.ui.results_buttons.clear();
        for (size_t i = 0; i < context.current_recommendations.size(); i++) {
            const auto& film = context.current_recommendations[i];
            ImageButton button;
            button.name = film.get_name();
            auto it = context.texture_cache.find(film.get_name());
            if (it != context.texture_cache.end()) {
                button.sprite.setTexture(it->second);
                sf::Vector2f o_size = sf::Vector2f(it->second.getSize());
                button.sprite.setScale(RESULT_TARGET_SIZE.x / o_size.x, RESULT_TARGET_SIZE.y / o_size.y);
            }
            int row = i / RESULTS_PER_ROW;
            int col = i % RESULTS_PER_ROW;
            float px = R_START_X + col * (RESULT_TARGET_SIZE.x + R_PADDING_X);
            float py = R_START_Y + row * (RESULT_TARGET_SIZE.y + R_PADDING_Y);
            button.sprite.setPosition(px, py);
            button.text = sf::Text(film.get_name(), context.font, FONT_SIZE_SMALL);
            button.text.setFillColor(TEXT_COLOR);
            button.text.setPosition(px + (RESULT_TARGET_SIZE.x - button.text.getGlobalBounds().width) / 2.f, py + RESULT_TARGET_SIZE.y + 10);
            context.ui.results_buttons.push_back(button);
        }
        for (auto& button : context.ui.results_buttons) {
            button.text.setFillColor(button.sprite.getGlobalBounds().contains(mouse_pos) ? HOVER_COLOR : TEXT_COLOR);
        }
    }
}

void render_login(AppContext& context) {
    float center_x = context.window.getSize().x / 2.0f;
    context.ui.main_title.setPosition(center_x, 200.f);
    context.ui.prompt_text.setPosition(center_x, 280.f);
    context.ui.input_box.setPosition(center_x, 325.f);
    context.ui.text_input_field.setPosition(context.ui.input_box.getPosition().x - 140.f, context.ui.input_box.getPosition().y - 15.f);

    context.window.draw(context.ui.main_title);
    context.window.draw(context.ui.prompt_text);
    context.window.draw(context.ui.input_box);
    context.window.draw(context.ui.text_input_field);
    context.window.draw(context.ui.caret);
}

void render_main_menu(AppContext& context) {
    float center_x = context.window.getSize().x / 2.0f;
    context.ui.menu_title.setPosition(center_x, 200.f);
    context.ui.genre_button.setPosition(center_x, 300.f);
    context.ui.cast_button.setPosition(center_x, 360.f);

    context.window.draw(context.ui.menu_title);
    context.window.draw(context.ui.genre_button);
    context.window.draw(context.ui.cast_button);
}

void render_selection_screen(AppContext& context, const sf::Text& title, const std::vector<ImageButton>& buttons) {
    context.window.draw(title);
    for (const auto& button : buttons) {
        context.window.draw(button.sprite);
        context.window.draw(button.text);
    }
}

void render_results(AppContext& context) {
    context.ui.results_title.setString(RESULTS_PROMPT);
    center_text(context.ui.results_title);
    context.ui.results_title.setPosition(context.window.getSize().x / 2.f, 50.f);
    
    if (context.current_recommendations.empty()) {
        sf::Text empty_text(NO_RESULTS_MSG, context.font, FONT_SIZE_BODY);
        center_text(empty_text);
        empty_text.setPosition(context.window.getSize().x / 2.f, 300.f);
        empty_text.setFillColor(TEXT_COLOR);
        context.window.draw(empty_text);
    } else {
        render_selection_screen(context, context.ui.results_title, context.ui.results_buttons);
    }
    context.ui.back_prompt.setString(BACK_TO_MENU_MSG);
    center_text(context.ui.back_prompt);
    context.ui.back_prompt.setPosition(context.window.getSize().x / 2.f, BACK_PROMPT_Y);
    context.window.draw(context.ui.back_prompt);
}

std::string wrap_text(const std::string& text, unsigned int line_width_chars) {
    std::string result;
    std::stringstream ss(text);
    std::string line;
    std::string word;
    
    while (std::getline(ss, line)) {
        std::stringstream line_ss(line);
        std::string current_line_out;
        while (line_ss >> word) {
            if (current_line_out.length() + word.length() + 1 > line_width_chars) {
                result += current_line_out + "\n";
                current_line_out = "";
            }
            if (!current_line_out.empty()) current_line_out += " ";
            current_line_out += word;
        }
        result += current_line_out + "\n";
    }
    return result;
}

void render_movie_details(AppContext& context) {
    if (!context.selected_film) return;

    sf::Text title(context.selected_film->get_name(), context.font, FONT_SIZE_TITLE);
    center_text(title);
    title.setPosition(context.window.getSize().x / 2.f, 50.f);
    title.setFillColor(ACCENT_COLOR);
    context.window.draw(title);

    auto it = context.texture_cache.find(context.selected_film->get_name());
    if (it != context.texture_cache.end()) {
        sf::Sprite poster(it->second);
        poster.setPosition(DETAILS_POSTER_X, DETAILS_POSTER_Y);
        poster.setScale(DETAILS_POSTER_WIDTH / it->second.getSize().x, DETAILS_POSTER_WIDTH / it->second.getSize().x);
        context.window.draw(poster);
    }

    FilmDetails details = context.app_logic.get_film_details(context.selected_film->get_name());
    
    sf::Text label_text("", context.font, FONT_SIZE_SMALL);
    label_text.setFillColor(ACCENT_COLOR);
    sf::Text value_text("", context.font, FONT_SIZE_SMALL);
    value_text.setFillColor(TEXT_COLOR);
    
    float current_y = DETAILS_TEXT_Y;
    auto draw_detail = [&](const std::string& label, const std::string& value, bool is_multiline = false) {
        if (!value.empty()) {
            label_text.setString(label);
            label_text.setPosition(DETAILS_TEXT_X, current_y);
            context.window.draw(label_text);
            
            value_text.setString(wrap_text(value, DETAILS_WRAP_CHARS));
            value_text.setPosition(DETAILS_TEXT_X + 180, current_y);
            context.window.draw(value_text);
            current_y += value_text.getLocalBounds().height + 20;
        }
    };
    
    draw_detail("Director:", details.director);
    draw_detail("Writers:", details.writers, true);
    draw_detail("Composer:", details.composer);

    if (!details.main_cast.empty()) {
        label_text.setString("Main Cast:");
        label_text.setPosition(DETAILS_TEXT_X, current_y);
        context.window.draw(label_text);
        current_y += 30;
        for (const auto& actor : details.main_cast) {
            value_text.setString("- " + actor);
            value_text.setPosition(DETAILS_TEXT_X + 20, current_y);
            context.window.draw(value_text);
            current_y += 25;
        }
    }
    current_y = std::max(current_y, DETAILS_POSTER_Y + 450.f);

    label_text.setString("[PLOT SUMMARY]");
    label_text.setPosition(50, current_y);
    context.window.draw(label_text);
    current_y += 30;

    value_text.setString(wrap_text(details.plot_summary, 80));
    value_text.setPosition(50, current_y);
    context.window.draw(value_text);
    
    
}

void render(AppContext& context) {
    context.window.clear(BG_COLOR);
    context.window.draw(context.ui.background_sprite);

    switch (context.currentState) {
        case AppState::Login: render_login(context); break;
        case AppState::MainMenu: render_main_menu(context); break;
        case AppState::GenreSelect: render_selection_screen(context, context.ui.genre_title, context.ui.genre_buttons); break;
        case AppState::CastSelect: render_selection_screen(context, context.ui.cast_title, context.ui.cast_buttons); break;
        case AppState::ShowResults: render_results(context); break;
        case AppState::MovieDetails: render_movie_details(context); break;
    }

    context.window.display();
}