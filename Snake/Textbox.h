#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
#include<string>


using MessageContainer = std::vector<std::string>;

class Textbox {

public:

    Textbox();
    Textbox(int visible, int char_size, int width, sf::Vector2f screen_pos);

    ~Textbox();

    void setup(int visible, int char_size, int width, sf::Vector2f screen_pos);
    void add(const std::string &message);
    void clear();

    void render(sf::RenderWindow &window);

private:

    MessageContainer m_messages;
    int m_num_visible;

    sf::RectangleShape m_backdrop;
    sf::Font m_font;
    sf::Text m_content;

};