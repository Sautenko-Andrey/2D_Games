#include "Game.h"


Game::Game()
: m_world{sf::Vector2u(800, 600), &m_textbox},
  m_snake{m_world.getBlockSize()},
  m_window{"Snake", sf::Vector2u(800, 600)}
{
    // Setting up class members
    // m_mushroom_texture.loadFromFile("graphics/mushroom.png");
    // m_mushroom.setTexture(m_mushroom_texture);
    // m_increment = sf::Vector2i(400, 400);

    srand(time(nullptr));

    m_textbox.setup(5, 14, 350, sf::Vector2f(225, 0));
    m_textbox.add("Seeded random number generator with: " +
                   std::to_string(time(NULL)));
}

Game::~Game(){
    // Empty destructor for now
}

void Game::handleInput(){
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
       m_snake.getPhysicalDirection() != Direction::Down)
    {
        m_snake.setDirection(Direction::Up);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
            m_snake.getPhysicalDirection() != Direction::Up)
    {
        m_snake.setDirection(Direction::Down);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
            m_snake.getPhysicalDirection() != Direction::Left)
    {
        m_snake.setDirection(Direction::Right);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
            m_snake.getPhysicalDirection() != Direction::Right)
    {
        m_snake.setDirection(Direction::Left);
    }

}

void Game::update(){

    /*
        Updating the position of our sprite each frame
    */

    m_window.update();  // Update window events

    // moveMushroom();


    // Snake speed in order to update the appropriate amount
    // of times per second
    float timestep = 1.0f / m_snake.getSpeed();

    if(m_elapsed_time.asSeconds() >= timestep){
        m_snake.tick();

        m_world.update(m_snake);
        m_elapsed_time -= sf::seconds(timestep);

        // If user lost
        if(m_snake.hasLost()){
            m_textbox.add("Game over! Score: " +
                           std::to_string(m_snake.getScore()));
            m_snake.reset();
        }
    }

}

void Game::render(){

    m_window.beginDraw();       // Clear

    // Render here
    m_world.render(*m_window.getRenderWindow());
    m_snake.render(*m_window.getRenderWindow());
    m_textbox.render(*m_window.getRenderWindow());

    m_window.endDraw();

}

Window* Game::getWindow(){

    return &m_window;

}

// void Game::moveMushroom(){

//     sf::Vector2u window_size = m_window.getWindowSize();

//     sf::Vector2u texture_size = m_mushroom_texture.getSize();

//     // Getting an elapsed time
//     float elapsed_time = m_elapsed_time.asSeconds();

//     if((m_mushroom.getPosition().x > window_size.x - texture_size.x &&
//         m_increment.x > 0) || (m_mushroom.getPosition().x < 0 &&
//         m_increment.x < 0)){
        
//         m_increment.x = -m_increment.x;
//     }

//     if((m_mushroom.getPosition().y > window_size.y - texture_size.y &&
//         m_increment.y > 0) || (m_mushroom.getPosition().y < 0 &&
//         m_increment.y < 0)){
        
//         m_increment.y = -m_increment.y;
//     }

//     m_mushroom.setPosition(
//         m_mushroom.getPosition().x + m_increment.x * elapsed_time,
//         m_mushroom.getPosition().y + m_increment.y * elapsed_time
//     );

// }

sf::Time Game::getElapsedTime(){
    return m_elapsed_time;
}



void Game::restartClock(){

    //m_elapsed_time = m_clock.restart();

    // Fixed time step
    m_elapsed_time += m_clock.restart();    
}
