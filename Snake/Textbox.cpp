#include"Textbox.h"


Textbox::Textbox(){
    setup(5, 9, 200, sf::Vector2f(0, 0));
}

Textbox::Textbox(int visible, int char_size,
                 int width, sf::Vector2f screen_pos){

    setup(visible, char_size, width, screen_pos);
}

Textbox::~Textbox(){

    clear();
}

void Textbox::setup(int visible, int char_size,
                    int width, sf::Vector2f screen_pos){

    m_num_visible = visible;

    sf::Vector2f offset(2.0f, 2.0f);

    m_font.loadFromFile("fonts/Movistar.ttf");
    m_content.setFont(m_font);
    m_content.setString("");
    m_content.setCharacterSize(char_size);
    m_content.setFillColor(sf::Color::White);
    m_content.setPosition(screen_pos + offset);

    m_backdrop.setSize(
        sf::Vector2f(width, (visible * (char_size * 1.2f)))
    );

    m_backdrop.setFillColor(sf::Color(90,90,90,90));
    m_backdrop.setPosition(screen_pos);
}

void Textbox::add(const std::string &message){
    
    m_messages.push_back(message);

    if(m_messages.size() < 6){
        return;
    }

    m_messages.erase(m_messages.begin());

}

void Textbox::clear(){
    m_messages.clear();
}

void Textbox::render(sf::RenderWindow &window){

    std::string content;

    for(auto &message : m_messages){
        content.append(message + '\n');
    }

    if(content != ""){
        m_content.setString(content);
        window.draw(m_backdrop);
        window.draw(m_content);
    }
}