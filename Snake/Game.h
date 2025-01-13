#pragma once
#include "Window.h"
#include "World.h"
#include "Snake.h"
#include "Textbox.h"



class Game {

public:

    Game();
    ~Game();

    void handleInput();

    void update();

    void render();

    Window* getWindow();

    sf::Time getElapsedTime();

    void restartClock();

private:

    //void moveMushroom();

    World m_world;

    Snake m_snake;

    Window m_window;

    Textbox m_textbox;

    sf::Texture m_mushroom_texture;

    sf::Sprite m_mushroom;

    sf::Vector2i m_increment;

    sf::Clock m_clock;

    sf::Time m_elapsed_time;

};