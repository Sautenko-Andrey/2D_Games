#pragma once
#include<SFML/Graphics.hpp>
#include"Snake.h"
#include "Textbox.h"

class World {

public:

    World(sf::Vector2u window_size, Textbox *textbox);

    int getBlockSize();

    void respawnApple();

    void update(Snake &player);

    void render(sf::RenderWindow &window);

private:

    sf::Vector2u m_window_size;

    sf::Vector2i m_item;

    int m_block_size;

    sf::CircleShape m_apple_shape;

    inline static constexpr int m_bounds_num{4};

    sf::RectangleShape m_bounds[m_bounds_num];

    Textbox *m_ptr_textbox{nullptr};

};