#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Window {

public:

    Window();

    Window(const std::string &title, const sf::Vector2u &size);

    ~Window();

    void beginDraw();  // Clear the window

    void endDraw();    // Display the changes

    void update();

    bool isDone();

    bool isFullScreen();

    sf::Vector2u getWindowSize();

    void toggleFullScreen();

    void draw(sf::Drawable &drawable);

    sf::RenderWindow* getRenderWindow();


private:

    void setUp(const std::string &title, const sf::Vector2u &size);

    void destroy();

    void create();

    sf::RenderWindow m_window;

    sf::Vector2u m_window_size;

    std::string m_window_title;

    bool m_is_done;

    bool m_is_full_screen;

};