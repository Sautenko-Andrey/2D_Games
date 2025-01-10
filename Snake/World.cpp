#include"World.h"


World::World(sf::Vector2u window_size)
{
    m_block_size = 16;

    m_window_size = window_size;

    respawnApple();

    m_apple_shape.setFillColor(sf::Color::Red);
    m_apple_shape.setRadius(m_block_size / 2);

    for(auto i{0}; i < m_bounds_num; ++i){
        m_bounds[i].setFillColor(sf::Color(150, 0, 0));

        if(!((i + 1) % 2)){
            m_bounds[i].setSize(sf::Vector2f(m_window_size.x, m_block_size));
        }
        else{
            m_bounds[i].setSize(sf::Vector2f(m_block_size, m_window_size.y));
        }

        if(i < 2){
            m_bounds[i].setPosition(0, 0);
        }
        else{
            m_bounds[i].setOrigin(m_bounds[i].getSize());
            m_bounds[i].setPosition(sf::Vector2f(m_window_size));
        }
    }
}


void World::respawnApple(){

    auto maxX{(m_window_size.x / m_block_size) - 2};

    auto maxY{(m_window_size.y / m_block_size) - 2};

    m_item = sf::Vector2i(rand() % maxX + 1, rand() % maxY + 1);

    m_apple_shape.setPosition(
        m_item.x * m_block_size,
        m_item.y * m_block_size
    );
}


void World::update(Snake &player){

    if(player.getPosition() == m_item){
        // snake eats an apple
        player.extend();
        player.increaseScore();
        respawnApple();
    }

    int grid_size_x{static_cast<int>(m_window_size.x / m_block_size)};
    int grid_size_y{static_cast<int>(m_window_size.y / m_block_size)};

    // Check collisions with boundaries
    if(player.getPosition().x <= 0 ||
       player.getPosition().y <= 0 ||
       player.getPosition().x >= grid_size_x - 1 ||
       player.getPosition().y >= grid_size_y - 1){
        
        // Game over
        player.lose();
    }
}


void World::render(sf::RenderWindow &window){
    for(auto i{0}; i < m_bounds_num; ++i){
        window.draw(m_bounds[i]);
    }

    window.draw(m_apple_shape);
}


int World::getBlockSize(){
    return m_block_size; 
}