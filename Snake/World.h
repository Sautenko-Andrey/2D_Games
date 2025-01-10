#pragma once
#include<SFML/Graphics.hpp>
#include"Snake.h"

class World {

public:

    explicit World(sf::Vector2u window_size);

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

};